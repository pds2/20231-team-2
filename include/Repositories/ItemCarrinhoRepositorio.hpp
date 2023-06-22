#pragma once

#ifndef ITEMCARRINHOREPOSITORIO_HPP
#define ITEMCARRINHOREPOSITORIO_HPP

#include "Carrinho.hpp"
#include "ItemCarrinho.hpp"
#include "RepositorioBase.hpp"
#include "ItemRepositorio.hpp"

/*
 * Repositório que permite o acesso aos itens dos carrinhos armazenados no banco de dados.
 */
class ItemCarrinhoRepositorio 
    : RepositorioBase<ItemCarrinho>
{
    private:
        std::string _tabela = "ItemCarrinho";
        ItemRepositorio* _itemRepositorio;

        /**
         * @brief Executa o comando para criar a tabela desse repositório no banco de dados.
        */
        void CreateTable();
        
        /**
         * @brief Converte um objeto retornado pelo banco de dados em um ponteiro.
         * @returns Um ponteiro pro objeto definitivo.
        */
        ItemCarrinho* ConverterParaEntidade(sqlite3_stmt* stmt);

        /**
         * @brief Insere um objeto no banco de dados.
         * @param entity Objeto que será inserido.
         */
        void Inserir(ItemCarrinho* entidade);

    public:   
        /**
         * @brief Instância uma nova comunicação de uma entidade com o banco de dados.
         */
        ItemCarrinhoRepositorio(ItemRepositorio* itemRepositorio);

        /**
         * @brief Carrega os itens de um carrinho na memória.
         */
        void CarregarItensNoCarrinho(Carrinho* carrinho);

        /**
         * @brief Atualiza um objeto do banco de dados.
         * @param entity Carrinho com os itens já atualizados.
         */
        void AtualizarItensDeUmCarrinho(Carrinho* carrinho);

        /**
         * @brief Deleta todos os itens de um carrinho.
         * @param entity Carrinho com os itens a serem deletados.
         */
        void DeletarTodosOsItensDeUmCarrinho(Carrinho* carrinho);  

        /**
         * @brief Deleta todos as relações de um item.
         * @param entity Item a ser removido.
         */
        void DeletarTodasAsRelacoesDeUmItem(Item* item);     
};

#endif