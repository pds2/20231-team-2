#pragma once

#ifndef CLIENTEREPOSITORIO_HPP
#define CLIENTEREPOSITORIO_HPP

#include "../Cliente.hpp"
#include "RepositorioBase.hpp"

/*
 * Repositório que permite o acesso aos clientes armazenados no banco de dados.
 */
class ClienteRepositorio 
    : public RepositorioBase<Cliente>
{
    private:
        std::string _tabela = "Cliente";

        /**
         * @brief Executa o comando para criar a tabela desse repositório no banco de dados.
        */
        void CreateTable();
        
        /**
         * @brief Converte um objeto retornado pelo banco de dados em um ponteiro.
         * @returns Um ponteiro pro objeto definitivo.
        */
        Cliente* ConverterParaEntidade(sqlite3_stmt* stmt);

    public:    
        /**
         * @brief Instância uma nova comunicação de uma entidade com o banco de dados.
         */
        ClienteRepositorio();

        /**
         * @brief Lista os objetos salvos no banco de dados.
         * @returns Uma lista de ponteiros para o objetos armazenados.
         */
        std::vector<Cliente*> ListarTodos();

        /**
         * @brief Busca um objeto no banco de dados.
         * @param id Id do objeto buscado.
         * @returns Um ponteiro para o objeto buscado.
         */
        Cliente* BuscaPorId(int id);

        /**
         * @brief Insere um objeto no banco de dados.
         * @param entity Objeto que será inserido.
         */
        void Inserir(Cliente* entidade);

        /**
         * @brief Atualiza um objeto do banco de dados.
         * @param entity Objeto que será atualizado.
         */
        void Atualizar(Cliente* entidade);
        
        /**
         * @brief Deleta um objeto do banco de dados.
         * @param entity Objeto que será deletado.
         */
        void Deletar(Cliente* entidade);
};

#endif