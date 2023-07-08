#pragma once

#ifndef ITEMCARRINHO_HPP
#define ITEMCARRINHO_HPP

#include <string>
#include "EntidadeBase.hpp"

/**
 * @class ItemCarrinho
 * @brief Classe responsável por relacionar um item a um carrinho.
 *
 * Essa classe representa a relação entre um item e um carrinho de compras.
 */
class ItemCarrinho : public EntidadeBase
{
private:
    int _idItem;     /**< ID do item. */
    int _idCarrinho; /**< ID do carrinho. */

public:
    /**
     * @brief Construtor da classe ItemCarrinho.
     * @param idItem ID do item.
     * @param idCarrinho ID do carrinho.
     */
    ItemCarrinho(int idItem, int idCarrinho);
};

#endif // ITEMCARRINHO_HPP
