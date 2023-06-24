#pragma once

#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include "DatabaseManager.hpp"
#include "ItemRepositorio.hpp"
#include "CupomRepositorio.hpp"
#include "ClienteRepositorio.hpp"
#include "CarteiraRepositorio.hpp"
#include "CarrinhoRepositorio.hpp"
#include "RestauranteRepositorio.hpp"

/**
 * Gerenciador dos banco de dados do sistema.
 */
class DatabaseManager 
{
    private:
        ItemRepositorio* _itemRepositorio;
        CupomRepositorio* _cupomRepositorio; 
        ClienteRepositorio* _clienteRepositorio;
        CarteiraRepositorio* _carteiraRepositorio;
        CarrinhoRepositorio* _carrinhoRepositorio;
        RestauranteRepositorio* _restauranteRepositorio;
        ItemCarrinhoRepositorio* _itemCarrinhoRepositorio;

    public:    
        /**
         * @brief Cria os repositórios que se possibilitam o acesso ao banco de dados.
        */
        DatabaseManager();

        /**
         * @brief Limpa a memória usada pelos ponteiros do sistema.
        */
        ~DatabaseManager();

        /**
         * @brief Retorna um ponteiro para o repositório de itens.
        */
        ItemRepositorio* GetItemRepositorio();

        /**
         * @brief Retorna um ponteiro para o repositório de cupons.
        */
        CupomRepositorio* GetCupomRepositorio();
        
        /**
         * @brief Retorna um ponteiro para o repositório de clientes.
        */
        ClienteRepositorio* GetClienteRepositorio();
        
        /**
         * @brief Retorna um ponteiro para o repositório de carteiras.
        */
        CarteiraRepositorio* GetCarteiraRepositorio();
        
        /**
         * @brief Retorna um ponteiro para o repositório de restaurantes.
        */
        RestauranteRepositorio* GetRestauranteRepositorio();

        /**
         * @brief Retorna um ponteiro para o repositório de carrinhos.
        */
        CarrinhoRepositorio* GetCarrinhoRepositorio();
};

#endif