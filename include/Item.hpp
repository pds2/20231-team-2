#pragma once

#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include "EntidadeBase.hpp"

/**
 * @enum ItemType
 * Um enumerador representando os tipodes de itens disponíveis.
 */
enum class ItemType
{
    BEBIDAS,            /**< Bebidas comuns */
    BEBIDAS_ALCOLICAS,  /**< Bebidas contendo alcool */
    FAST_FOOD,          /**< Comidas pré-processadas */
    PRATO_FEITO,        /**< Prato feito */
    DOCES,              /**< Doces */
};

/*
 *          Essa classe representa uma exceção que será levantada quando o percetual
 * de desconto for inválido, ou seja, o percentual ser menor ou igual a zero ou superior a 100.
 */
class desconto_invalido_e {};

/*
 *  Essa classe é responsável por armazenar e inicializar as informações básicas
 *              dos itens(representação genérica de um produto)
 */
class Item 
    : public EntidadeBase
{
    private:
        std::string _nome;
        std::string _descricao;
        ItemType _tipo;
        double _precoBase;
        double _precoComDesconto;
        bool _descontoAplicado;
    
    public:

    /*
    * @brief Intância um novo item(produto).
    */
    Item(std::string nome, std::string descricao, ItemType tipo, double precoBase);

    /*
    * @brief Retorna o nome desse item.
    */
    std::string GetNome();

    /*
    * @brief Retorna a descrição desse item.
    */
    std::string GetDescricao();

    /*
    * @brief Retorna o tipo desse item.
    */
    ItemType GetTipo();

    /*
    * @brief Retorna o preço base desse item.
    */
    double GetPrecoBase();

    /*
    * @brief Retorna o preço atual desse item. Esse método considera possíveis descontos aplicados.
    */
    double GetPrecoAtual();

    /*
    * @brief Retorna verdadeiro caso exista um desconto aplicado a esse item.
    */
    bool ExiteUmDescontoAplicado();

    /**
     * @brief Aplica um desconto sobre o preço base.
     * @param percentualDesconto Pode variar de 1 a 100.
     */
    void AplicarDesconto(int percentualDesconto);

    /**
     * @brief Remove o desconto aplicado a esse item, caso exista.
    */
   void RemoverDescontoAtual();
};

#endif