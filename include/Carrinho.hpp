#ifndef CARRINHO_HPP
#define CARRINHO_HPP

#include <vector>

#include "Item.hpp"

/*
 * @brief Essa classe representa uma exceção que será leançada quando um item 
 * que não está no carrinho de compras tentar ser retirado dele.
 */
class item_nao_existe_no_carrinho_e {};

/*
 * @brief Essa classe representa um carrinho de compras que poderá ser usado
 * pelos clientes para adicionar seus Itens.
 */
class Carrinho{
  private:
  std::vector<Item> _compras;
  double _valorTotal;

  public:

  /*
   * @brief Instancia um carrinho de compras,
   * inicialmente vazio.
   */
  Carrinho();


  /*
   * @brief Retorna o vetor contendo todas as compras adicionadas
   * nele.
   */
  std::vector get_carrinho();

  /*
   * @brief Retorna o valor total do carrinho de compras.
   */
  double get_valorTotal();

  /*
   * @brief Adiciona um Item ao carrinho.
   */
  void adicionarItem(std::string item);

  /*
   * @brief Remove um Item do carrinho.
   */
  void removerItem();


  
};

#endif