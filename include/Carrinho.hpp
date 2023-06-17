#ifndef CARRINHO_HPP
#define CARRINHO_HPP

#include <vector>

#include "Item.hpp"
#include "EntidadeBase.hpp"

/*
 * @brief Essa classe representa uma exceção que será lançada quando um item 
 * que não está no carrinho de compras tentar ser retirado dele.
 */
class item_nao_existe_no_carrinho_e {};

/*
 * @brief Essa classe representa uma exceção que será lançada quando um item
 * tentar ser removido de um carrinho vazio(que não tem itens).
 */
class carrinho_vazio_e {};

/*
 * @brief Essa classe representa um carrinho de compras que poderá ser usado
 * pelos clientes para adicionar seus Itens.
 */
class Carrinho: public EntidadeBase{
  private:
  std::vector<Item*> _compras;
  double _valorTotal;

  public:

  /*
   * @brief Instancia um carrinho de compras,
   * inicialmente vazio.
   */
  Carrinho();

  /*
   * @brief Retorna o valor total do carrinho de compras.
   */
  double GetValorTotal();

  /*
   * @brief Retorna o vetor contendo todas as compras adicionadas
   * nele.
   */
  std::vector<Item*> GetCarrinho();

  /*
   * @brief Adiciona um Item ao carrinho.
   */
  void AdicionarItem(Item *item);

  /*
   * @brief Remove um Item do carrinho.
   */
  void RemoverItem(Item *item);

  /*
   * @brief Remove todos os itens do carrinho.
   */
  void LimparCarrinho();  
};

#endif