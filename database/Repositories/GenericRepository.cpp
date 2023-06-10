#include <string>
#include <variant>

#include "../../include/Repositories/GenericRepository.hpp"
#include "../../libs/sqllite/sqlite3.h"

GenericRepository::GenericRepository() 
{
    const char* databaseOPath = _databaseOPath.c_str();
    sqlite3_open(databaseOPath, &_database);
}

GenericRepository::~GenericRepository() 
{
    sqlite3_close(_database);
}

bool GenericRepository::ExecuteSQL(std::string sql)
{
    char* err;
    const char* sqlPointer = sql.c_str();
    int rc = sqlite3_exec(_database, sqlPointer, nullptr, nullptr, &err);
    
    return rc == SQLITE_OK;
}

bool GenericRepository::ExecuteSQLReplace(std::string sql, std::map<std::string, std::variant<int, double, std::string>> valuesToReplace)
{
    std::string sqlReplaced = sql;

    for (auto& [key, value] : valuesToReplace)
    {
        sqlReplaced = this->Replace(sqlReplaced, key, value);
    }

    return ExecuteSQL(sqlReplaced);
}

std::string GenericRepository::Replace(std::string str, std::string placeholder, std::variant<int, double, std::string> replacement)
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

sqlite3_stmt* GenericRepository::Select(std::string sql)
{
    const char* sqlPointer = sql.c_str();

    sqlite3_stmt * stmt;

    sqlite3_prepare_v2(_database, sqlPointer, -1, &stmt, 0);
    sqlite3_step(stmt);

    return stmt;
}