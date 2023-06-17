#pragma once

#ifndef REPOSITORIOBASE_HPP
#define REPOSITORIOBASE_HPP

#include <map>
#include <vector>
#include <variant>

#include "../EntidadeBase.hpp"
#include "../../libs/sqllite/sqlite3.h"

class RepositorioBase 
{    
    private:
        /**
         * @brief Busca o último identificador inserido no banco de dados.
         * @returns id do objeto inserido.
         */
        int GetUltimoIdInserido();

    protected:
        std::string _diretorioDatabase = "database.db";
        sqlite3* _database;
        std::map<int, EntidadeBase*> _entidades;

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

        /**
         * @brief Converte um objeto retornado pelo banco de dados em um ponteiro.
         * @returns ponteiro pro objeto definitivo.
        */
        virtual EntidadeBase* ConverterParaEntidade(sqlite3_stmt* stmt) = 0;

        /**
         * @brief Lista os objetos salvos no banco de dados.
         * @param tabela nome da tabela no banco de dados.
         * @returns Uma lista de ponteiros para o objetos armazenados.
         */
        void CarregarTodosOsDadosNaMemoria(std::string tabela);

        /**
         * @brief Lista os objetos salvos no banco de dados.
         * @param tabela nome da tabela no banco de dados.
         * @param where restrição de listagem.
         * @returns Uma lista de ponteiros para o objetos armazenados.
         */
        void CarregarTodosOsDadosNaMemoria(std::string tabela, std::string where);

        /**
         * @brief Busca um objeto no banco de dados.
         * @param tabela nome da tabela no banco de dados.
         * @param id Id do objeto buscado.
         * @returns Um ponteiro para o objeto buscado.
         */
        EntidadeBase* BuscaPorId(std::string tabela, int id);

        /**
         * @brief Deleta um objeto do banco de dados.
         * @param tabela nome da tabela no banco de dados.
         * @param id Id do objeto alvo.
         */
        void Deletar(std::string tabela, EntidadeBase * entidade);

        /**
         * @brief Insere um item na lista de entidades, buscando seu Id novo no banco.
         * @param entidade Um ponteiro pra entidade.
        */
       void InserirNovoRegistro(EntidadeBase* entidade);
    public:
        /**
         * @brief Instância uma nova comunicação de uma entidade com o banco de dados.
         */
        RepositorioBase();

        /**
         * @brief Limpa os ponteiros gerenciados por esse repositório.
         */
        ~RepositorioBase();
};

#endif