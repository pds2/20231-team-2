#include <map>
#include <vector>
#include <variant>

#include "Item.hpp"
#include "Carrinho.hpp"
#include "Sqlite/sqlite3.h"
#include "Repositories/ItemCarrinhoRepositorio.hpp"

ItemCarrinhoRepositorio::ItemCarrinhoRepositorio(ItemRepositorio* itemRepositorio)
{
    _itemRepositorio = itemRepositorio;

    CreateTable();
}

ItemCarrinho* ItemCarrinhoRepositorio::ConverterParaEntidade(sqlite3_stmt* stmt)
{
    int id = sqlite3_column_int(stmt, 0);
    std::string criacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    std::string atualizacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));

    int idItem = sqlite3_column_int(stmt, 3);
    int idCarrinho = sqlite3_column_int(stmt, 4);

    ItemCarrinho* entidade = new ItemCarrinho(idItem, idCarrinho);
    entidade->SetarDadosBase(criacao, atualizacao, id);

    return entidade;
}

void ItemCarrinhoRepositorio::Inserir(ItemCarrinho* entidade)
{
    std::string query = "INSERT INTO " + _tabela + " (dataDeCriacao, dataUltimaAtualizacao, idItem, idCarrinho) VALUES ('{0}', '{1}', {2}, {3});";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entidade->GetDataDeCriacao() },
        { "{1}", entidade->GetDataUltimaAtualizacao() },
        { "{2}", entidade->_idItem },
        { "{3}", entidade->_idCarrinho }
    };        

    ExecuteSQLReplace(query, values);
    InserirNovoRegistro(entidade);
}

void ItemCarrinhoRepositorio::CarregarItensNoCarrinho(Carrinho* carrinho)
{
    int idCarrinho = carrinho->GetId();

    std::string idString = std::to_string(idCarrinho);
    std::string where = "WHERE idCarrinho = " + idString + ";";
    RepositorioBase::CarregarTodosOsDadosNaMemoria(_tabela, where);

    std::vector<Item*> itensDoCarrinho;
    
    for(auto pair : _entidades)
    {
        ItemCarrinho* relacao = pair.second;
        if (relacao->GetId() == idCarrinho) 
        {
            Item* item = _itemRepositorio->BuscaPorId(relacao->_idItem);
            if (item)
                itensDoCarrinho.push_back(item);
        }
    }

    carrinho->SetItens(itensDoCarrinho);
}

void ItemCarrinhoRepositorio::AtualizarItensDeUmCarrinho(Carrinho* carrinho)
{
    // Mapeando as relações salvas na memória
    std::map<int, ItemCarrinho*> relacoes;
    for(auto pair : _entidades)
    {   
        ItemCarrinho* relacao = pair.second;
        if (relacao->_idCarrinho == carrinho->GetId())
            relacoes[relacao->_idItem] = relacao;
    }

    // Mapeando os itens atuais do carrinho
    std::map<int, Item*> itens;
    for(Item* item : carrinho->GetCarrinho())
    {   
        itens[item->GetId()] = item;
    }

    // Deletando as relações que não constam nos itens atuais
    for(auto pair : relacoes)
    {
        ItemCarrinho* relacao = pair.second;
        if (!(itens.count(relacao->_idItem)))
            Deletar(_tabela, relacao);
    }

    // Inserindo as relações que não existiam
    for(auto pair : itens)
    {
        Item* item = pair.second;
        if (relacoes.count(item->GetId()) <= 0)
        {
            ItemCarrinho* entidade = new ItemCarrinho(item->GetId(), carrinho->GetId());
            Inserir(entidade);
        }
    }
}

void ItemCarrinhoRepositorio::DeletarTodosOsItensDeUmCarrinho(Carrinho* carrinho)
{
    for(auto pair : _entidades)
    {   
        ItemCarrinho* relacao = pair.second;
        if (relacao->_idCarrinho == carrinho->GetId())
            Deletar(_tabela, relacao);
    }
}

void ItemCarrinhoRepositorio::DeletarTodasAsRelacoesDeUmItem(Item* item)
{
    int idItem = item->GetId();

    std::string idString = std::to_string(idItem);
    std::string where = "WHERE idItem = " + idString + ";";
    RepositorioBase::CarregarTodosOsDadosNaMemoria(_tabela, where);

    for(auto pair : _entidades)
    {
        ItemCarrinho* relacao = pair.second;
        if (relacao->GetId() == idItem) 
            Deletar(_tabela, relacao);
    }
}

void ItemCarrinhoRepositorio::CreateTable()
{
    std::string query = "CREATE TABLE IF NOT EXISTS " + _tabela + " ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "dataDeCriacao TEXT,"
                        "dataUltimaAtualizacao TEXT,"
                        "idItem INTEGER,"
                        "idCarrinho INTEGER"
                        ");";

    ExecuteSQL(query);
}