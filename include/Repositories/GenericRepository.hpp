#pragma once

#ifndef GENERICREPOSITORY_HPP
#define GENERICREPOSITORY_HPP

#include <map>
#include <vector>
#include <variant>
#include "../EntidadeBase.hpp"
#include "../../libs/sqllite/sqlite3.h"

class GenericRepository 
{    
    protected:
        std::string _databaseOPath = "./database/sqlitedata.db";
        sqlite3* _database;

        /**
         * @brief Executa um comando sql no banco de dados.
         * @returns true caso tudo ocorra corretamente.
         */
        bool ExecuteSQL(std::string sql);

        /**
         * @brief Executa um comando sql no banco de dados substituindo as chaves pelos valores informados.
         * @returns true caso tudo ocorra corretamente.
         */
        bool ExecuteSQLReplace(std::string sql, std::map<std::string, std::variant<int, double, std::string>> valuesToReplace);

        /**
         * @brief Busca dados no banco de acordo com a query informada..
         * @returns Um ponteiro para o iterador retornado pelo banco.
         */
        sqlite3_stmt* Select(std::string sql);

        /**
         * @brief Substitui um trecho de uma string por outro..
         * @returns string com o placeholder substituido pelo valor.
         */
        std::string Replace(std::string str, std::string placeholder, std::variant<int, double, std::string> replacement);
    public:
        /**
         * @brief Instância uma nova comunicação de uma entidade com o banco de dados.
         */
        GenericRepository();

        /**
         * @brief Limpa os ponteiros gerenciados por esse repositório.
         */
        ~GenericRepository();
};

#endif