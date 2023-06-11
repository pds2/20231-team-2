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

ItemRepositorio::~ItemRepositorio()
{
    for (auto entity : _entidades)
    {
        delete entity;
    }
}

Item* ItemRepositorio::ConverterParaEntidade(sqlite3_stmt* stmt)
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

std::vector<Item*> ItemRepositorio::ListarTodos()
{
    std::vector<Item*> items;

    std::string query = "SELECT * FROM Item;";
    sqlite3_stmt* stmt = Select(query);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Item* entity = ConverterParaEntidade(stmt);
        items.push_back(entity);
    }

    sqlite3_finalize(stmt);

    return items;
}

Item* ItemRepositorio::BuscaPorId(int id)
{
    for(Item* item : _entidades)
    {
        if (item->GetId() == id)
            return item;
    }

    std::string query = "SELECT * FROM Item WHERE id = '" + std::to_string(id) + "';";
    
    sqlite3_stmt* stmt = Select(query);
    sqlite3_step(stmt);
    Item* entity = ConverterParaEntidade(stmt);
    sqlite3_finalize(stmt);

    _entidades.push_back(entity);
    return entity;
}

void ItemRepositorio::Inserir(Item* entity)
{
    std::string query = "INSERT INTO Item (nome, descricao, tipo, precoBase, precoComDesconto, dataDeCriacao, dataUltimaAtualizacao) VALUES ('{0}', '{1}', {2}, {3}, {4}, '{5}', '{6}');";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entity->GetNome() },
        { "{1}", entity->GetDescricao() },
        { "{2}", static_cast<int>(entity->GetTipo()) },
        { "{3}", entity->GetPrecoBase() },
        { "{4}", entity->GetPrecoAtual() },
        { "{5}", entity->GetDataDeCriacao() },
        { "{6}", entity->GetDataUltimaAtualizacao() },
    };        

    ExecuteSQLReplace(query, values);
    _entidades.push_back(entity);
}

void ItemRepositorio::Atualizar(Item* entity)
{
    entity->AtualizarAgora();

    std::string query = "UPDATE Item SET nome = '{0}', descricao = '{1}', tipo = {2}, precoBase = {3}, precoComDesconto = {4}, dataDeCriacao = '{5}', dataUltimaAtualizacao = '{6}' WHERE id = {7};";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entity->GetNome() },
        { "{1}", entity->GetDescricao() },
        { "{2}", static_cast<int>(entity->GetTipo()) },
        { "{3}", entity->GetPrecoBase() },
        { "{4}", entity->GetPrecoAtual() },
        { "{5}", entity->GetDataDeCriacao() },
        { "{6}", entity->GetDataUltimaAtualizacao() },
        { "{7}", entity->GetId() }
    };        

    ExecuteSQLReplace(query, values);
}

void ItemRepositorio::Deletar(Item* entity)
{
    std::string query = "DELETE FROM Item WHERE id = " + std::to_string(entity->GetId()) + ";";
    ExecuteSQL(query);

    for (auto it = _entidades.begin(); it != _entidades.end(); ++it)
    {
        if ((*it)->GetId() == entity->GetId())
        {
            _entidades.erase(it);
            delete (*it);
            break;
        }
    }
}

void ItemRepositorio::CreateTable()
{
    std::string query = "CREATE TABLE IF NOT EXISTS Item ("
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