#pragma once

#ifndef CARRINHO_HPP
#define CARRINHO_HPP

#include <vector>

#include "Item.hpp"
#include "EntidadeBase.hpp"
#include "Cupom.hpp"

/**
 * @class item_nao_existe_no_carrinho_e
 * @brief Exceção lançada quando um item que não está no carrinho de compras tenta ser retirado dele.
 */
class item_nao_existe_no_carrinho_e {};

/**
 * @class carrinho_vazio_e
 * @brief Exceção lançada quando tenta-se remover um item de um carrinho vazio.
 */
class carrinho_vazio_e {};

/**
 * @class um_cupom_ja_foi_usado_e
 * @brief Exceção lançada quando mais de um cupom é aplicado no carrinho.
 */
class um_cupom_ja_foi_usado_e {};

/**
 * @class encerrar_pedido_primeiro_e
 * @brief Exceção lançada quando se tenta usar um cupom antes de finalizar o pedido.
 */
class encerrar_pedido_primeiro_e {};

/**
 * @class Carrinho
 * @brief Classe que representa um carrinho de compras.
 *
 * Essa classe representa um carrinho de compras que pode ser usado pelos clientes para adicionar itens.
 */
class Carrinho : public EntidadeBase {
private:
    std::vector<Item*> _compras;
    double _valorTotal;
    bool _pedidoEncerrado;
    int _idCliente;
    bool _descontoAplicado;

public:
    /**
     * @brief Construtor da classe Carrinho.
     * @param idCliente O identificador do cliente no banco.
     */
    Carrinho(int idCliente);

    /**
     * @brief Retorna o valor total do carrinho de compras.
     * @return O valor total do carrinho de compras.
     */
    double GetValorTotal();

    /**
     * @brief Aplica um desconto no valor total do carrinho.
     * @param cupom O cupom de desconto a ser aplicado.
     */
    void AplicarDesconto(Cupom* cupom);

    /**
     * @brief Define o valor total do carrinho.
     * @param valorTotal O valor total do carrinho.
     */
    void SetValorTotal(double valorTotal);

    /**
     * @brief Retorna o vetor contendo todas as compras adicionadas ao carrinho.
     * @return Um vetor contendo os itens do carrinho.
     */
    std::vector<Item*> GetCarrinho();

    /**
     * @brief Define os itens do carrinho.
     * @param itens O vetor de itens a ser definido como itens do carrinho.
     */
    void SetItens(std::vector<Item*> itens);

    /**
     * @brief Adiciona um item ao carrinho.
     * @param item O item a ser adicionado ao carrinho.
     */
    void AdicionarItem(Item* item);

    /**
     * @brief Remove um item do carrinho.
     * @param item O item a ser removido do carrinho.
     */
    void RemoverItem(Item* item);

    /**
     * @brief Remove todos os itens do carrinho.
     */
    void LimparCarrinho();

    /**
     * @brief Encerra o pedido quando o cliente já pagou pelos itens.
     */
    void Encerrar();

    /**
     * @brief Verifica se o pedido está encerrado.
     * @return true se o pedido está encerrado, false caso contrário.
     */
    bool EstaEncerrado();

    /**
     * @brief Define o status do carrinho.
     * @param status O status do carrinho.
     */
    void SetStatus(bool status);

    /**
     * @brief Retorna o ID do cliente.
     * @return O ID do cliente.
     */
    int GetIdCliente();

    /**
     * @brief Verifica se um desconto foi aplicado no carrinho.
     * @return true se um desconto foi aplicado, false caso contrário.
     */
    bool GetDescontoAplicado();
};

#endif // CARRINHO_HPP
