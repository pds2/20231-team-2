#include "../../libs/sqllite/sqlite3.h"
#include "../../include/Repositories/ItemRepository.hpp"
#include "../../include/Item.hpp"

#include <vector>
#include <map>
#include <iostream>
#include <variant>

ItemRepository::ItemRepository()
{
    CreateTable();
}

ItemRepository::~ItemRepository()
{
    for (auto entity : _entities)
    {
        delete entity;
    }
}

std::vector<Item*> ItemRepository::GetAll()
{
    return std::vector<Item*>();
}

Item* ConvertToEntity(sqlite3_stmt* stmt)
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

Item* ItemRepository::GetById(int id)
{
    for(Item* item : _entities)
    {
        if (item->GetId() == id)
            return item;
    }

    std::string query = "SELECT (id, nome, descricao, tipo, precoBase, precoComDesconto, descontoAplicado, dataDeCriacao, dataUltimaAtualizacao) " 
                        "FROM Item WHERE id = " + std::to_string(id) + ";";
    
    sqlite3_stmt* stmt = Select(query);

    Item* entity = ConvertToEntity(stmt);
    _entities.push_back(entity);
    return entity;
}

void ItemRepository::Insert(Item* entity)
{
    std::string query = "INSERT INTO Item (id, nome, descricao, tipo, precoBase, precoComDesconto, descontoAplicado, dataDeCriacao, dataUltimaAtualizacao) VALUES (0, '{0}', '{1}', {2}, {3}, {4}, {5}, '{6}', '{7}');";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entity->GetNome() },
        { "{1}", entity->GetDescricao() },
        { "{2}", static_cast<int>(entity->GetTipo()) },
        { "{3}", entity->GetPrecoBase() },
        { "{4}", entity->GetPrecoAtual() },
        { "{5}", entity->ExisteUmDescontoAplicado() },
        { "{6}", entity->GetDataDeCriacao() },
        { "{7}", entity->GetDataUltimaAtualizacao() },
    };        

    ExecuteSQLReplace(query, values);
    _entities.push_back(entity);
}

void ItemRepository::Update(Item* entity)
{
    entity->AtualizarAgora();

    std::string query = "UPDATE Item SET nome = '{0}', descricao = '{1}', tipo = {2}, precoBase = {3}, precoComDesconto = {4}, descontoAplicado = {5}, dataDeCriacao = '{6}', dataUltimaAtualizacao = '{7}' WHERE id = {8};";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entity->GetNome() },
        { "{1}", entity->GetDescricao() },
        { "{2}", static_cast<int>(entity->GetTipo()) },
        { "{3}", entity->GetPrecoBase() },
        { "{4}", entity->GetPrecoAtual() },
        { "{5}", entity->ExisteUmDescontoAplicado() },
        { "{6}", entity->GetDataDeCriacao() },
        { "{7}", entity->GetDataUltimaAtualizacao() },
        { "{8}", entity->GetId() }
    };        

    ExecuteSQLReplace(query, values);
}

void ItemRepository::Delete(Item* entity)
{
    std::string query = "DELETE FROM Item WHERE id = " + std::to_string(entity->GetId()) + ";";
    ExecuteSQL(query);

    for (auto it = _entities.begin(); it != _entities.end(); ++it)
    {
        Item* item = static_cast<Item*>(*it);
        if (item->GetId() == entity->GetId())
        {
            _entities.erase(it);
            delete item;
            break;
        }
    }
}

void ItemRepository::CreateTable()
{
    std::string query = "CREATE TABLE IF NOT EXISTS Item ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "nome TEXT,"
                        "descricao TEXT,"
                        "tipo INTEGER,"
                        "precoBase REAL,"
                        "precoComDesconto REAL,"
                        "descontoAplicado INTEGER,"
                        "dataDeCriacao TEXT,"
                        "dataUltimaAtualizacao TEXT);";

    ExecuteSQL(query);
}