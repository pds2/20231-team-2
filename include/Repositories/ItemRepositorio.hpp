#pragma once

#ifndef ITEMREPOSITORIO_HPP
#define ITEMREPOSITORIO_HPP

#include "RepositorioBase.hpp"
#include "../Item.hpp"

/*
 * Repositório que permite o acesso aos itens armazenados no banco de dados.
 */
class ItemRepositorio 
    : public RepositorioBase
{
    private:
        std::string _tabela = "Item";

        /**
         * @brief Executa o comando para criar a tabela desse repositório no banco de dados.
        */
        void CreateTable();

        /**
         * @brief Converte um ponteiro para entidade base para um ponteiro da entidade desse repositório.
         * @param entidadeBase Ponteiro pra entidade origem.
         * @returns Um ponteiro para o objeto convertido.
        */
        Item* Cast(EntidadeBase* entidadeBase);
        
        /**
         * @brief Converte um objeto retornado pelo banco de dados em um ponteiro.
         * @returns Um ponteiro pro objeto definitivo.
        */
        EntidadeBase* ConverterParaEntidade(sqlite3_stmt* stmt);

    public:   
        /**
         * @brief Instância uma nova comunicação de uma entidade com o banco de dados.
         */
        ItemRepositorio();

        /**
         * @brief Lista os objetos salvos no banco de dados.
         * @returns Uma lista de ponteiros para o objetos armazenados.
         */
        std::vector<Item*> ListarTodos();

        /**
         * @brief Busca um objeto no banco de dados.
         * @param id Id do objeto buscado.
         * @returns Um ponteiro para o objeto buscado.
         */
        Item* BuscaPorId(int id);

        /**
         * @brief Insere um objeto no banco de dados.
         * @param entity Objeto que será inserido.
         */
        void Inserir(Item* entidade);

        /**
         * @brief Atualiza um objeto do banco de dados.
         * @param entity Objeto que será atualizado.
         */
        void Atualizar(Item* entidade);
        
        /**
         * @brief Deleta um objeto do banco de dados.
         * @param entity Objeto que será deletado.
         */
        void Deletar(Item* entidade);
};

#endif