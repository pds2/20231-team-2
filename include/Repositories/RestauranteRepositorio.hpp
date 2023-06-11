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
        std::string _tabela = "Restaurante";

        /**
         * @brief Executa o comando para criar a tabela desse repositório no banco de dados.
        */
        void CreateTable();

        /**
         * @brief Converte um ponteiro para entidade base para um ponteiro da entidade desse repositório.
         * @param entidadeBase Ponteiro pra entidade origem.
         * @returns Um ponteiro para o objeto convertido.
        */
        Restaurante* Cast(EntidadeBase* entidadeBase);
        
        /**
         * @brief Converte um objeto retornado pelo banco de dados em um ponteiro.
         * @returns Um ponteiro pro objeto definitivo.
        */
        EntidadeBase* ConverterParaEntidade(sqlite3_stmt* stmt);

    public:    
        /**
         * @brief Instância uma nova comunicação de uma entidade com o banco de dados.
         */
        RestauranteRepositorio();

        /**
         * @brief Lista os objetos salvos no banco de dados.
         * @returns Uma lista de ponteiros para o objetos armazenados.
         */
        std::vector<Restaurante*> ListarTodos();

        /**
         * @brief Busca um objeto no banco de dados.
         * @param id Id do objeto buscado.
         * @returns Um ponteiro para o objeto buscado.
         */
        Restaurante* BuscaPorId(int id);

        /**
         * @brief Insere um objeto no banco de dados.
         * @param entity Objeto que será inserido.
         */
        void Inserir(Restaurante* entidade);

        /**
         * @brief Atualiza um objeto do banco de dados.
         * @param entity Objeto que será atualizado.
         */
        void Atualizar(Restaurante* entidade);
        
        /**
         * @brief Deleta um objeto do banco de dados.
         * @param entity Objeto que será deletado.
         */
        void Deletar(Restaurante* entidade);
};

#endif