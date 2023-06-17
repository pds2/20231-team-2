#include <map>
#include <vector>
#include <variant>

#include "../../include/Item.hpp"
#include "../../libs/sqllite/sqlite3.h"
#include "../../include/Restaurante.hpp"
#include "../../include/Repositories/ItemRepositorio.hpp"

ItemRepositorio::ItemRepositorio()
{
    CreateTable();
}

EntidadeBase* ItemRepositorio::ConverterParaEntidade(sqlite3_stmt* stmt)
{    
    int id = sqlite3_column_int(stmt, 0);
    std::string nome(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    int idRestaurante = sqlite3_column_int(stmt, 2);
    std::string descricao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
    int tipo = sqlite3_column_int(stmt, 4);
    double precoBase = sqlite3_column_double(stmt, 5);
    double precoComDesconto = sqlite3_column_double(stmt, 6);
    std::string criacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
    std::string atualizacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));

    Item* entity = new Item(nome, descricao, static_cast<ItemType>(tipo), precoBase, idRestaurante);
    entity->SetPrecoComDesconto(precoComDesconto);
    entity->SetarDadosBase(criacao, atualizacao, id);

    return entity;
}

Item* ItemRepositorio::Cast(EntidadeBase* entidadeBase)
{
    return dynamic_cast<Item*>(entidadeBase);
}

void ItemRepositorio::CarregarItensNoRestaurante(Restaurante* restaurante)
{
    std::string idRestaurante = std::to_string(restaurante->GetId());
    std::string where = "WHERE idRestaurante = " + idRestaurante;
    RepositorioBase::CarregarTodosOsDadosNaMemoria(_tabela);

    std::vector<Item*> itens;

    for(auto pair : _entidades)
    {
        Item* atual = Cast(pair.second);
        if (atual->GetIdRestaurante() == restaurante->GetId())
        {
            restaurante->AdicionarItem(atual);
        }
    }
}

Item* ItemRepositorio::BuscaPorId(int id)
{
    EntidadeBase* baseComum = RepositorioBase::BuscaPorId(_tabela, id);
    return Cast(baseComum);
}

void ItemRepositorio::Inserir(Item* entidade)
{
    std::string query = "INSERT INTO " + _tabela + " (idRestaurante, nome, descricao, tipo, precoBase, precoComDesconto, dataDeCriacao, dataUltimaAtualizacao) VALUES ({0}, '{1}', '{2}', {3}, {4}, {5}, '{6}', '{7}');";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{1}", entidade->GetIdRestaurante() },
        { "{1}", entidade->GetNome() },
        { "{2}", entidade->GetDescricao() },
        { "{3}", static_cast<int>(entidade->GetTipo()) },
        { "{4}", entidade->GetPrecoBase() },
        { "{5}", entidade->GetPrecoAtual() },
        { "{6}", entidade->GetDataDeCriacao() },
        { "{7}", entidade->GetDataUltimaAtualizacao() },
    };        

    ExecuteSQLReplace(query, values);
    InserirNovoRegistro(entidade);
}

void ItemRepositorio::Atualizar(Item* entidade)
{
    entidade->AtualizarAgora();

    std::string query = "UPDATE " + _tabela + " SET nome = '{0}', idRestaurante = {1}, descricao = '{2}', tipo = {3}, precoBase = {4}, precoComDesconto = {5}, dataUltimaAtualizacao = '{6}' WHERE id = {7};";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entidade->GetNome() },
        { "{1}", entidade->GetIdRestaurante() },
        { "{2}", entidade->GetDescricao() },
        { "{3}", static_cast<int>(entidade->GetTipo()) },
        { "{4}", entidade->GetPrecoBase() },
        { "{5}", entidade->GetPrecoAtual() },
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
    std::string query = "CREATE TABLE IF NOT EXISTS " + _tabela + " ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "nome TEXT,"
                        "idRestaurante INTEGER,"
                        "descricao TEXT,"
                        "tipo INTEGER,"
                        "precoBase REAL,"
                        "precoComDesconto REAL,"
                        "dataDeCriacao TEXT,"
                        "dataUltimaAtualizacao TEXT);";

    ExecuteSQL(query);
}