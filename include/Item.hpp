#pragma once

#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include "EntidadeBase.hpp"

/**
 * @enum ItemType
 * Enumeração representando os tipos de itens disponíveis.
 */
enum class ItemType
{
    BEBIDAS,            /**< Bebidas comuns. */
    BEBIDAS_ALCOLICAS, /**< Bebidas contendo álcool. */
    FAST_FOOD,          /**< Comidas pré-processadas. */
    PRATO_FEITO,        /**< Prato feito. */
    DOCES,              /**< Doces. */
};

/**
 *          Essa classe representa uma exceção que será levantada quando o percetual
 * de desconto for inválido, ou seja, o percentual ser menor ou igual a zero ou superior a 100.
 */
class desconto_invalido_e {};

/**
 * @class Item
 * @brief Classe responsável por armazenar e inicializar as informações básicas dos itens (representação genérica de um produto).
 *
 */
class Item : public EntidadeBase
{
private:
    std::string _nome;
    std::string _descricao;
    ItemType _tipo;
    double _precoBase;
    double _precoComDesconto;
    int _idRestaurante;

public:
    /**
     * @brief Construtor da classe Item.
     * @param nome O nome do item.
     * @param descricao A descrição do item.
     * @param tipo O tipo do item.
     * @param precoBase O preço base do item.
     * @param idRestaurante O ID do restaurante que oferece o item.
     */
    Item(std::string nome, std::string descricao, ItemType tipo, double precoBase, int idRestaurante);

    /**
     * @brief Retorna o nome do item.
     * @return O nome do item.
     */
    std::string GetNome();

    /**
     * @brief Retorna a descrição do item.
     * @return A descrição do item.
     */
    std::string GetDescricao();

    /**
     * @brief Retorna o tipo do item.
     * @return O tipo do item.
     */
    ItemType GetTipo();

    /**
     * @brief Retorna o preço base do item.
     * @return O preço base do item.
     */
    double GetPrecoBase();

    /**
     * @brief Retorna o preço atual do item. Esse método considera possíveis descontos aplicados.
     * @return O preço atual do item.
     */
    double GetPrecoAtual();

    /**
     * @brief Define o preço com desconto do item.
     * @param precoComDesconto O preço com desconto do item.
     */
    void SetPrecoComDesconto(double precoComDesconto);

    /**
     * @brief Verifica se existe um desconto aplicado ao item.
     * @return `true` se existe um desconto aplicado, `false` caso contrário.
     */
    bool ExisteUmDescontoAplicado();

    /**
     * @brief Aplica um desconto sobre o preço base do item.
     * @param percentualDesconto O percentual de desconto a ser aplicado. Deve ser um valor entre 1 e 100.
     * @throw desconto_invalido_e Se o percentual de desconto for inválido.
     */
    void AplicarDesconto(int percentualDesconto);

    /**
     * @brief Remove o desconto atualmente aplicado ao item.
     */
    void RemoverDescontoAtual();

    /**
     * @brief Retorna o ID do restaurante que oferece o item.
     * @return O ID do restaurante.
     */
    int GetIdRestaurante();
};

#endif // ITEM_HPP
