#pragma once

#ifndef RESTAURANTEREPOSITORIO_HPP
#define RESTAURANTEREPOSITORIO_HPP

#include "Restaurante.hpp"
#include "RepositorioBase.hpp"
#include "ItemRepositorio.hpp"
#include "ItemCarrinhoRepositorio.hpp"

/*
 * Repositório que permite o acesso aos restaurantes armazenados no banco de dados.
 */
class RestauranteRepositorio 
    : RepositorioBase<Restaurante>
{
    private:
        std::string _tabela = "Restaurante";
        ItemRepositorio* _itemRepositorio;
        ItemCarrinhoRepositorio* _itemCarrinhoRepositorio;

        /**
         * @brief Executa o comando para criar a tabela desse repositório no banco de dados.
        */
        void CreateTable();
        
        /**
         * @brief Converte um objeto retornado pelo banco de dados em um ponteiro.
         * @returns Um ponteiro pro objeto definitivo.
        */
        Restaurante* ConverterParaEntidade(sqlite3_stmt* stmt);

    public:    
        /**
         * @brief Instância uma nova comunicação de uma entidade com o banco de dados.
         * @param itemRepositorio Referência para acesso aos itens.
         * @param _itemCarrinhoRepositorio Referência para acesso aos itens dos carrinhos.
         */
        RestauranteRepositorio(ItemRepositorio* itemRepositorio, ItemCarrinhoRepositorio* itemCarrinhoRepositorio);

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
         * @brief Busca um objeto no banco de dados.
         * @param login login do objeto buscado.
         * @returns Um ponteiro para o objeto buscado.
         */
        Restaurante* BuscaPorLogin(std::string login);

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

        /**
         * @brief Atualiza os itens relacionados a um restaurante.
         * @param entity Objeto que será atualizado.
        */
        void AtualizarItens(Restaurante* entidade);
};

#endif