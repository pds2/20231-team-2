#ifndef CARRINHO_HPP
#define CARRINHO_HPP

#include <vector>
#include <string>

/*
 * @brief Essa classe representa um carrinho de compras que poderá ser usado
 * pelos clientes para adicionar seus Itens(ver com Erik)
 */
class Carrinho{
  private:
  std::vector<std::string> _compras;
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
  double get_valorTotal();

  /*
   * @brief Adiciona um Item ao carrinho
   */
  void adicionarItem(std::string item);

  /*
   * @brief Remove um Item do carrinho
   */
  void removerItem();


  
};

#endif