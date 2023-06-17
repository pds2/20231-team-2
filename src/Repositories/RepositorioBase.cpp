#include <string>
#include <variant>

#include "../../libs/sqllite/sqlite3.h"
#include "../../include/Repositories/RepositorioBase.hpp"

RepositorioBase::RepositorioBase() 
{
    const char* diretorio = _diretorioDatabase.c_str();
    sqlite3_open(diretorio, &_database);
}

RepositorioBase::~RepositorioBase() 
{
    for(auto pair : _entidades)
    {
        auto entidade = pair.second;
        delete entidade;
    }

    sqlite3_close(_database);
}

bool RepositorioBase::ExecuteSQL(std::string sql)
{
    char* err;
    const char* sqlPointer = sql.c_str();
    int rc = sqlite3_exec(_database, sqlPointer, nullptr, nullptr, &err);
    
    return rc == SQLITE_OK;
}

bool RepositorioBase::ExecuteSQLReplace(std::string sql, std::map<std::string, std::variant<int, double, std::string>> valuesToReplace)
{
    std::string sqlReplaced = sql;

    for (auto& [key, value] : valuesToReplace)
    {
        sqlReplaced = this->Replace(sqlReplaced, key, value);
    }

    return ExecuteSQL(sqlReplaced);
}

std::string RepositorioBase::Replace(std::string str, std::string placeholder, std::variant<int, double, std::string> replacement)
{
    std::string result = str;
    size_t pos = result.find(placeholder);

    while (pos != std::string::npos)
    {
        if (std::holds_alternative<int>(replacement))
        {
            int rep = std::get<int>(replacement);
            result.replace(pos, placeholder.length(), std::to_string(rep));
        }
        else if (std::holds_alternative<double>(replacement))
        {
            double rep = std::get<double>(replacement);
            result.replace(pos, placeholder.length(), std::to_string(rep));
        }
        else if (std::holds_alternative<std::string>(replacement))
        {
            std::string rep = std::get<std::string>(replacement);
            result.replace(pos, placeholder.length(), rep);
        }

        pos = result.find(placeholder, pos + placeholder.length());
    }

    return result;
}

sqlite3_stmt* RepositorioBase::Select(std::string sql)
{
    const char* sqlPointer = sql.c_str();

    sqlite3_stmt * stmt;

    sqlite3_prepare_v2(_database, sqlPointer, -1, &stmt, 0);

    return stmt;
}

void RepositorioBase::CarregarTodosOsDadosNaMemoria(std::string tabela)
{
    CarregarTodosOsDadosNaMemoria(tabela, "");
}

void RepositorioBase::CarregarTodosOsDadosNaMemoria(std::string tabela, std::string where)
{
    std::string query = "SELECT * FROM "+ tabela + " " + where + ";";
    sqlite3_stmt* stmt = Select(query);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        EntidadeBase* entidade = ConverterParaEntidade(stmt);

        int entitadeId = entidade->GetId();
        if (_entidades.count(entitadeId) > 0)
        {
            delete entidade;
        }
        else
        {
            _entidades[entitadeId] = entidade;
        }
    }

    sqlite3_finalize(stmt);
}

EntidadeBase* RepositorioBase::BuscaPorId(std::string tabela, int id)
{
    for(auto pair : _entidades)
    {
        EntidadeBase* entidade = pair.second;
        if (entidade->GetId() == id)
            return entidade;
    }

    std::string idString = std::to_string(id);
    std::string query = "SELECT * FROM " + tabela + " WHERE id = '" + idString + "';";
    
    sqlite3_stmt* stmt = Select(query);
    
    sqlite3_step(stmt);
    EntidadeBase* entidade = ConverterParaEntidade(stmt);
    sqlite3_finalize(stmt);

    _entidades[id] = entidade;

    return entidade;
}

void RepositorioBase::Deletar(std::string tabela, EntidadeBase * entidade)
{
    int id = entidade->GetId();

    std::string idString = std::to_string(id);
    std::string query = "DELETE FROM " + tabela + " WHERE id = " + idString + ";";

    ExecuteSQL(query);

    _entidades.erase(id);
    delete entidade;
}

int RepositorioBase::GetUltimoIdInserido()
{
    std::string queryId = "SELECT last_insert_rowid();";
    sqlite3_stmt* stmt = Select(queryId);
    
    sqlite3_step(stmt);
    int id = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    return id;
}

void RepositorioBase::InserirNovoRegistro(EntidadeBase* entidade)
{
    int id = GetUltimoIdInserido();
    entidade->SetId(id);

    _entidades[id] = entidade;
}