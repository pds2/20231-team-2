#pragma once

#ifndef ITEMREPOSITORY_HPP
#define ITEMREPOSITORY_HPP

#include "GenericRepository.hpp"
#include "../Item.hpp"

/*
 * Repositório que permite o acesso aos itens armazenados no banco de dados.
 */
class ItemRepository 
    : public GenericRepository
{
    private:
        std::vector<Item*> _entities;
        void CreateTable();

    public:    
        /**
         * @brief Instância uma nova comunicação de uma entidade com o banco de dados.
         */
        ItemRepository();

        /**
         * @brief Limpa os ponteiros gerenciados por esse repositório.
         */
        ~ItemRepository();

        /**
         * @brief Converte um objeto retornado pelo banco de dados em um ponteiro.
         * @returns ponteiro pro objeto definitivo.
        */
        Item* ConvertToEntity(sqlite3_stmt* stmt);

        /**
         * @brief Lista os objetos salvos no banco de dados.
         * @returns Uma lista de ponteiros para o objetos armazenados.
         */
        std::vector<Item*> GetAll();

        /**
         * @brief Deleta um objeto do banco de dados.
         * @param id Id do objeto buscado.
         * @returns Um ponteiro para o objeto buscado.
         */
        Item* GetById(int id);

        /**
         * @brief Insere um objeto no banco de dados.
         * @param entity Objeto que será inserido.
         */
        void Insert(Item* entity);

        /**
         * @brief Atualiza um objeto do banco de dados.
         * @param entity Objeto que será atualizado.
         */
        void Update(Item* entity);
        
        /**
         * @brief Deleta um objeto do banco de dados.
         * @param entity Objeto que será deletado.
         */
        void Delete(Item* entity);
};

#endif