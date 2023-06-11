#pragma once

#ifndef ITEMREPOSITORY_HPP
#define ITEMREPOSITORY_HPP

#include "RepositorioBase.hpp"
#include "../Restaurante.hpp"

/*
 * Repositório que permite o acesso aos restaurantes armazenados no banco de dados.
 */
class RestauranteRepositorio 
    : public RepositorioBase
{
    private:
        std::vector<Restaurante*> _entidades;
        void CreateTable();

    public:    
        /**
         * @brief Instância uma nova comunicação de uma entidade com o banco de dados.
         */
        RestauranteRepositorio();

        /**
         * @brief Limpa os ponteiros gerenciados por esse repositório.
         */
        ~RestauranteRepositorio();

        /**
         * @brief Converte um objeto retornado pelo banco de dados em um ponteiro.
         * @returns ponteiro pro objeto definitivo.
        */
        Restaurante* ConverterParaEntidade(sqlite3_stmt* stmt);

        /**
         * @brief Lista os objetos salvos no banco de dados.
         * @returns Uma lista de ponteiros para o objetos armazenados.
         */
        std::vector<Restaurante*> ListarTodos();

        /**
         * @brief Deleta um objeto do banco de dados.
         * @param id Id do objeto buscado.
         * @returns Um ponteiro para o objeto buscado.
         */
        Restaurante* BuscaPorId(int id);

        /**
         * @brief Insere um objeto no banco de dados.
         * @param entity Objeto que será inserido.
         */
        void Inserir(Restaurante* entity);

        /**
         * @brief Atualiza um objeto do banco de dados.
         * @param entity Objeto que será atualizado.
         */
        void Atualizar(Restaurante* entity);
        
        /**
         * @brief Deleta um objeto do banco de dados.
         * @param entity Objeto que será deletado.
         */
        void Deletar(Restaurante* entity);
};

#endif