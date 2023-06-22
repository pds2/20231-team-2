#pragma once

#ifndef CARRINHOREPOSITORIO_HPP
#define CARRINHOREPOSITORIO_HPP

#include "Carrinho.hpp"
#include "RepositorioBase.hpp"
#include "ItemCarrinhoRepositorio.hpp"

/*
 * Repositório que permite o acesso aos carrinhos armazenadas no banco de dados.
 */
class CarrinhoRepositorio 
    : RepositorioBase<Carrinho>
{
    private:
        std::string _tabela = "Carrinho";
        ItemCarrinhoRepositorio* _itemCarrinhoRepositorio;

        /**
         * @brief Executa o comando para criar a tabela desse repositório no banco de dados.
        */
        void CreateTable();
        
        /**
         * @brief Converte um objeto retornado pelo banco de dados em um ponteiro.
         * @returns Um ponteiro pro objeto definitivo.
        */
        Carrinho* ConverterParaEntidade(sqlite3_stmt* stmt);

    public:   
        /**
         * @brief Instância uma nova comunicação de uma entidade com o banco de dados.
         * @param itemCarrinhoRepositorio Acesso aos itens que compõem um carrinho.
         */
        CarrinhoRepositorio(ItemCarrinhoRepositorio* itemCarrinhoRepositorio);

        /**
         * @brief Busca um objeto no banco de dados.
         * @param id Id do objeto buscado.
         * @returns Um ponteiro para o objeto buscado.
         */
        Carrinho* BuscaPorId(int id);

        /**
         * @brief Busca um objeto no banco de dados.
         * @param id Id do cliente.
         * @returns Um vector para os objeto buscado.
         */
        std::vector<Carrinho*> BuscaPorIdDoCliente(int idCliente);

        /**
         * @brief Insere um objeto no banco de dados.
         * @param entity Objeto que será inserido.
         */
        void Inserir(Carrinho* entidade);

        /**
         * @brief Atualiza um objeto do banco de dados.
         * @param entity Objeto que será atualizado.
         */
        void Atualizar(Carrinho* entidade);
        
        /**
         * @brief Deleta um objeto do banco de dados.
         * @param entity Objeto que será deletado.
         */
        void Deletar(Carrinho* entidade);
};

#endif