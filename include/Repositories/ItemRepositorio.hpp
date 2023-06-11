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
        std::vector<Item*> _entidades;
        void CreateTable();

    public:    
        /**
         * @brief Instância uma nova comunicação de uma entidade com o banco de dados.
         */
        ItemRepositorio();

        /**
         * @brief Limpa os ponteiros gerenciados por esse repositório.
         */
        ~ItemRepositorio();

        /**
         * @brief Converte um objeto retornado pelo banco de dados em um ponteiro.
         * @returns ponteiro pro objeto definitivo.
        */
        Item* ConverterParaEntidade(sqlite3_stmt* stmt);

        /**
         * @brief Lista os objetos salvos no banco de dados.
         * @returns Uma lista de ponteiros para o objetos armazenados.
         */
        std::vector<Item*> ListarTodos();

        /**
         * @brief Deleta um objeto do banco de dados.
         * @param id Id do objeto buscado.
         * @returns Um ponteiro para o objeto buscado.
         */
        Item* BuscaPorId(int id);

        /**
         * @brief Insere um objeto no banco de dados.
         * @param entity Objeto que será inserido.
         */
        void Inserir(Item* entity);

        /**
         * @brief Atualiza um objeto do banco de dados.
         * @param entity Objeto que será atualizado.
         */
        void Atualizar(Item* entity);
        
        /**
         * @brief Deleta um objeto do banco de dados.
         * @param entity Objeto que será deletado.
         */
        void Deletar(Item* entity);
};

#endif