#include <vector>
#include <map>
#include <variant>

#include "../../libs/sqllite/sqlite3.h"
#include "../../include/Repositories/ItemRepositorio.hpp"
#include "../../include/Item.hpp"

ItemRepositorio::ItemRepositorio()
{
    CreateTable();
}

EntidadeBase* ItemRepositorio::ConverterParaEntidade(sqlite3_stmt* stmt)
{    
    int id = sqlite3_column_int(stmt, 0);
    std::string nome(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    std::string descricao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    int tipo = sqlite3_column_int(stmt, 3);
    double precoBase = sqlite3_column_double(stmt, 4);
    double precoComDesconto = sqlite3_column_double(stmt, 5);
    std::string criacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
    std::string atualizacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));

    Item* entity = new Item(nome, descricao, static_cast<ItemType>(tipo), precoBase);
    entity->SetPrecoComDesconto(precoComDesconto);
    entity->SetarDadosBase(criacao, atualizacao, id);

    return entity;
}

Item* ItemRepositorio::Cast(EntidadeBase* entidadeBase)
{
    return dynamic_cast<Item*>(entidadeBase);
}

std::vector<Item*> ItemRepositorio::ListarTodos()
{
    RepositorioBase::CarregarTodosOsDadosNaMemoria(_tabela);

    std::vector<Item*> itens;

    for(auto pair : _entidades)
    {
        itens.push_back(Cast(pair.second));
    }

    return itens;
}

Item* ItemRepositorio::BuscaPorId(int id)
{
    EntidadeBase* baseComum = RepositorioBase::BuscaPorId(_tabela, id);
    return Cast(baseComum);
}

void ItemRepositorio::Inserir(Item* entidade)
{
    std::string query = "INSERT INTO +" + _tabela + " (nome, descricao, tipo, precoBase, precoComDesconto, dataDeCriacao, dataUltimaAtualizacao) VALUES ('{0}', '{1}', {2}, {3}, {4}, '{5}', '{6}');";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entidade->GetNome() },
        { "{1}", entidade->GetDescricao() },
        { "{2}", static_cast<int>(entidade->GetTipo()) },
        { "{3}", entidade->GetPrecoBase() },
        { "{4}", entidade->GetPrecoAtual() },
        { "{5}", entidade->GetDataDeCriacao() },
        { "{6}", entidade->GetDataUltimaAtualizacao() },
    };        

    ExecuteSQLReplace(query, values);

    _entidades[entidade->GetId()] = entidade;
}

void ItemRepositorio::Atualizar(Item* entidade)
{
    entidade->AtualizarAgora();

    std::string query = "UPDATE +" + _tabela + " SET nome = '{0}', descricao = '{1}', tipo = {2}, precoBase = {3}, precoComDesconto = {4}, dataDeCriacao = '{5}', dataUltimaAtualizacao = '{6}' WHERE id = {7};";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entidade->GetNome() },
        { "{1}", entidade->GetDescricao() },
        { "{2}", static_cast<int>(entidade->GetTipo()) },
        { "{3}", entidade->GetPrecoBase() },
        { "{4}", entidade->GetPrecoAtual() },
        { "{5}", entidade->GetDataDeCriacao() },
        { "{6}", entidade->GetDataUltimaAtualizacao() },
        { "{7}", entidade->GetId() }
    };        

    ExecuteSQLReplace(query, values);
}

void ItemRepositorio::Deletar(Item* entidade)
{
    RepositorioBase::Deletar(_tabela, entidade);
}

void ItemRepositorio::CreateTable()
{
    std::string query = "CREATE TABLE IF NOT EXISTS +" + _tabela + " ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "nome TEXT,"
                        "descricao TEXT,"
                        "tipo INTEGER,"
                        "precoBase REAL,"
                        "precoComDesconto REAL,"
                        "dataDeCriacao TEXT,"
                        "dataUltimaAtualizacao TEXT);";

    ExecuteSQL(query);
}