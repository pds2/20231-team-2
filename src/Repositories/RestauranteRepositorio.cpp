#include <vector>
#include <map>
#include <variant>

#include "../../libs/sqllite/sqlite3.h"
#include "../../include/Repositories/RestauranteRepositorio.hpp"
#include "../../include/Restaurante.hpp"

RestauranteRepositorio::RestauranteRepositorio()
{
    CreateTable();
}

RestauranteRepositorio::~RestauranteRepositorio()
{
    for (auto entity : _entidades)
    {
        delete entity;
    }
}

Restaurante* RestauranteRepositorio::ConverterParaEntidade(sqlite3_stmt* stmt)
{    
    int id = sqlite3_column_int(stmt, 0);
    std::string criacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    std::string atualizacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));

    std::string cnpj(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
    std::string nome(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
    std::string login(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
    std::string senha(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));

    Restaurante* entity = new Restaurante(nome, login, senha, cnpj);
    entity->SetarDadosBase(criacao, atualizacao, id);

    return entity;
}

std::vector<Restaurante*> RestauranteRepositorio::ListarTodos()
{
    std::vector<Restaurante*> entities;

    std::string query = "SELECT * FROM Restaurante;";
    sqlite3_stmt* stmt = Select(query);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Restaurante* entity = ConverterParaEntidade(stmt);
        entities.push_back(entity);
    }

    sqlite3_finalize(stmt);

    return entities;
}

Restaurante* RestauranteRepositorio::BuscaPorId(int id)
{
    for(Restaurante* entity : _entidades)
    {
        if (entity->GetId() == id)
            return entity;
    }

    std::string query = "SELECT * FROM Restaurante WHERE id = '" + std::to_string(id) + "';";
    
    sqlite3_stmt* stmt = Select(query);
    sqlite3_step(stmt);
    Restaurante* entity = ConverterParaEntidade(stmt);
    sqlite3_finalize(stmt);

    _entidades.push_back(entity);
    return entity;
}

void RestauranteRepositorio::Inserir(Restaurante* entity)
{
    std::string query = "INSERT INTO Restaurante (nome, dataDeCriacao, dataUltimaAtualizacao, cnpj, nome, login, senha) VALUES ('{0}', '{1}', '{2}', '{3}', '{4}', '{5}', '{6}');";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entity->GetNome() },
        { "{1}", entity->GetDataDeCriacao() },
        { "{2}", entity->GetDataUltimaAtualizacao() },
        { "{3}", entity->GetCNPJ() },
        { "{4}", entity->GetNome() },
        { "{5}", entity->GetLogin() },
        { "{6}", entity->GetSenha() },
    };        

    ExecuteSQLReplace(query, values);
    _entidades.push_back(entity);
}

void RestauranteRepositorio::Atualizar(Restaurante* entity)
{
    entity->AtualizarAgora();
    
    std::string query = "UPDATE Restaurante SET nome = '{0}', dataUltimaAtualizacao = '{1}', cnpj = '{2}', login = '{3}', senha = '{4}' WHERE id = {5};";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entity->GetNome() },
        { "{1}", entity->GetDataUltimaAtualizacao() },
        { "{2}", entity->GetCNPJ() },
        { "{3}", entity->GetLogin() },
        { "{4}", entity->GetSenha() },
        { "{5}", entity->GetId() },
    };

    ExecuteSQLReplace(query, values);
}

void RestauranteRepositorio::Deletar(Restaurante* entity)
{
    std::string query = "DELETE FROM Restaurante WHERE id = " + std::to_string(entity->GetId()) + ";";
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

void RestauranteRepositorio::CreateTable()
{
    std::string query = "CREATE TABLE IF NOT EXISTS Restaurante ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "dataDeCriacao TEXT,"
                        "dataUltimaAtualizacao TEXT,"
                        "cnpj TEXT,"
                        "nome TEXT,"
                        "login TEXT,"
                        "senha TEXT"
                        ");";

    ExecuteSQL(query);
}