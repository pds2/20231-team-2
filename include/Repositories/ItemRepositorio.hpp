#pragma once

#ifndef ITEMREPOSITORIO_HPP
#define ITEMREPOSITORIO_HPP

#include "../Item.hpp"
#include "RepositorioBase.hpp"

/*
 * Repositório que permite o acesso aos itens armazenados no banco de dados.
 */
class ItemRepositorio 
    : RepositorioBase<Item>
{
    private:
        std::string _tabela = "Item";

        /**
         * @brief Executa o comando para criar a tabela desse repositório no banco de dados.
        */
        void CreateTable();
        
        /**
         * @brief Converte um objeto retornado pelo banco de dados em um ponteiro.
         * @returns Um ponteiro pro objeto definitivo.
        */
        Item* ConverterParaEntidade(sqlite3_stmt* stmt);

    public:   
        /**
         * @brief Instância uma nova comunicação de uma entidade com o banco de dados.
         */
        ItemRepositorio();

        /**
         * @brief Carrega os itens de um restaurante na memória.
         */
        void CarregarItensNoRestaurante(Restaurante* restaurante);

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