#pragma once

#ifndef REPOSITORIOBASE_HPP
#define REPOSITORIOBASE_HPP

#include <map>
#include <vector>
#include <variant>

#include "EntidadeBase.hpp"
#include "Sqlite/sqlite3.h"

template <class Tipo> 
class RepositorioBase 
{    
    private:
        /**
         * @brief Busca o último identificador inserido no banco de dados.
         * @returns id do objeto inserido.
         */
        int GetUltimoIdInserido()
        {
            std::string queryId = "SELECT last_insert_rowid();";
            sqlite3_stmt* stmt = Select(queryId);
            
            sqlite3_step(stmt);
            int id = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);

            return id;
        }

    protected:
        std::string _diretorioDatabase = "database.db";
        sqlite3* _database;
        std::map<int, Tipo*> _entidades;

        /**
         * @brief Executa o comando para criar a tabela desse repositório no banco de dados.
        */
        virtual void CreateTable() = 0;

        /**
         * @brief Converte um objeto retornado pelo banco de dados em um ponteiro.
         * @returns ponteiro pro objeto definitivo.
        */
        virtual Tipo* ConverterParaEntidade(sqlite3_stmt* stmt) = 0;

        /**
         * @brief Executa um comando sql no banco de dados.
         * @returns true caso tudo ocorra corretamente.
         */
        bool ExecuteSQL(std::string sql)
        {
            char* err;
            const char* sqlPointer = sql.c_str();
            int rc = sqlite3_exec(_database, sqlPointer, nullptr, nullptr, &err);
            
            return rc == SQLITE_OK;
        }

        /**
         * @brief Executa um comando sql no banco de dados substituindo as chaves pelos valores informados.
         * @returns true caso tudo ocorra corretamente.
         */
        bool ExecuteSQLReplace(std::string sql, std::map<std::string, std::variant<int, double, std::string>> valuesToReplace)
        {
            std::string sqlReplaced = sql;

            for (auto& [key, value] : valuesToReplace)
            {
                sqlReplaced = this->Replace(sqlReplaced, key, value);
            }

            return ExecuteSQL(sqlReplaced);
        }

        /**
         * @brief Busca dados no banco de acordo com a query informada..
         * @returns Um ponteiro para o iterador retornado pelo banco.
         */
        sqlite3_stmt* Select(std::string sql)
        {
            const char* sqlPointer = sql.c_str();

            sqlite3_stmt * stmt;

            sqlite3_prepare_v2(_database, sqlPointer, -1, &stmt, 0);

            return stmt;
        }

        /**
         * @brief Substitui um trecho de uma string por outro..
         * @returns string com o placeholder substituido pelo valor.
         */
        std::string Replace(std::string str, std::string placeholder, std::variant<int, double, std::string> replacement)
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

        /**
         * @brief Lista os objetos salvos no banco de dados.
         * @param tabela nome da tabela no banco de dados.
         * @returns Uma lista de ponteiros para o objetos armazenados.
         */
        void CarregarTodosOsDadosNaMemoria(std::string tabela)
        {
            CarregarTodosOsDadosNaMemoria(tabela, "");
        }

        /**
         * @brief Lista os objetos salvos no banco de dados.
         * @param tabela nome da tabela no banco de dados.
         * @param where restrição de listagem.
         * @returns Uma lista de ponteiros para o objetos armazenados.
         */
        void CarregarTodosOsDadosNaMemoria(std::string tabela, std::string where)
        {
            std::string query = "SELECT * FROM "+ tabela + " " + where + ";";
            sqlite3_stmt* stmt = Select(query);

            while (sqlite3_step(stmt) == SQLITE_ROW)
            {
                Tipo* entidade = ConverterParaEntidade(stmt);

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

        /**
         * @brief Busca um objeto no banco de dados.
         * @param tabela nome da tabela no banco de dados.
         * @param id Id do objeto buscado.
         * @returns Um ponteiro para o objeto buscado.
         */
        Tipo* BuscaPorId(std::string tabela, int id)
        {
            for(auto pair : _entidades)
            {
                Tipo* entidade = pair.second;
                if (entidade->GetId() == id)
                    return entidade;
            }

            std::string idString = std::to_string(id);
            std::string query = "SELECT * FROM " + tabela + " WHERE id = '" + idString + "';";
            
            sqlite3_stmt* stmt = Select(query);
            
            sqlite3_step(stmt);
            Tipo* entidade = ConverterParaEntidade(stmt);
            sqlite3_finalize(stmt);

            _entidades[id] = entidade;

            return entidade;
        }

        /**
         * @brief Deleta um objeto do banco de dados.
         * @param tabela nome da tabela no banco de dados.
         * @param id Id do objeto alvo.
         */
        void Deletar(std::string tabela, EntidadeBase * entidade)
        {
            int id = entidade->GetId();

            std::string idString = std::to_string(id);
            std::string query = "DELETE FROM " + tabela + " WHERE id = " + idString + ";";

            ExecuteSQL(query);

            _entidades.erase(id);
            delete entidade;
        }

        /**
         * @brief Insere um item na lista de entidades, buscando seu Id novo no banco.
         * @param entidade Um ponteiro pra entidade.
        */
        void InserirNovoRegistro(Tipo* entidade)
        {
            int id = GetUltimoIdInserido();
            entidade->SetId(id);

            _entidades[id] = entidade;
        }

    public:
        /**
         * @brief Instância uma nova comunicação de uma entidade com o banco de dados.
         */
        RepositorioBase()
        {
            const char* diretorio = _diretorioDatabase.c_str();
            sqlite3_open(diretorio, &_database);

            CreateTable();
        }

        /**
         * @brief Limpa os ponteiros gerenciados por esse repositório.
         */
        virtual ~RepositorioBase()
        {
            for(auto pair : _entidades)
            {
                auto entidade = pair.second;
                delete entidade;
            }

            sqlite3_close(_database);
        }
};

#endif