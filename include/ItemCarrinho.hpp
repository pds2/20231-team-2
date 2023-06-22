#pragma once

#ifndef ITEMCARRINHO_HPP
#define ITEMCARRINHO_HPP

#include <string>
#include "EntidadeBase.hpp"

/**
 *  Essa classe é responsável por relacionar um item a um carrinho
 */
class ItemCarrinho 
    : public EntidadeBase
{ 
    public:
        /**
         * @brief Id do item.
        */
        int _idItem;

        /**
         * @brief Id do carrinho.
        */
        int _idCarrinho;

        /**
         * @brief Intância um novo item(produto).
         */
        ItemCarrinho(int idItem, int idCarrinho);
};

#endif