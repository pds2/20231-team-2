#ifndef CARRINHO_HPP
#define CARRINHO_HPP

#include <vector>

#include "Item.hpp"
#include "EntidadeBase.hpp"
#include "Cupom.hpp"

/**
 * @brief Essa classe representa uma exceção que será lançada quando um item 
 * que não está no carrinho de compras tentar ser retirado dele.
 */
class item_nao_existe_no_carrinho_e {};

/**
 * @brief Essa classe representa uma exceção que será lançada quando um item
 * tentar ser removido de um carrinho vazio(que não tem itens).
 */
class carrinho_vazio_e {};

/**
 * @brief Essa classe representa uma exceção que será lançada quando mais
 * de um cupom tentar ser aplicado no carrinho.
 */
class um_cupom_ja_foi_usado_e {};

/**
 * @brief Essa classe representa uma exceção que será lançada quando o
 * cliente tentar usar o cupom antes de finalizar o pedido
 */
class encerrar_pedido_primeiro_e {};

/**
 * @brief Essa classe representa um carrinho de compras que poderá ser usado
 * pelos clientes para adicionar seus Itens.
 */
class Carrinho: public EntidadeBase{
  private:
  std::vector<Item*> _compras;
  double _valorTotal;
  bool _pedidoEncerrado;
  int _idCliente;
  bool _descontoAplicado;

  public:

  /**
   * @brief Instancia um carrinho de compras,
   * inicialmente vazio.
   * @param idCliente Identificador do cliente no banco.
   */
  Carrinho(int idCliente);

  /**
   * @brief Retorna o valor total do carrinho de compras.
   */
  double GetValorTotal();

  /**
   * @brief Aplica um desconto no valor total do carrinho.
  */
  void AplicarDesconto(Cupom *cupom);

  /**
   * @brief Seta o valor total do carrinho.
  */
  void SetValorTotal(double valorTotal);

  /**
   * @brief Retorna o vetor contendo todas as compras adicionadas
   * nele.
   */
  std::vector<Item*> GetCarrinho();

  /**
   * @brief Seta os itens desse carrinho.
  */
  void SetItens(std::vector<Item*> itens);

  /**
   * @brief Adiciona um Item ao carrinho.
   */
  void AdicionarItem(Item *item);

  /**
   * @brief Remove um Item do carrinho.
   */
  void RemoverItem(Item *item);

  /**
   * @brief Remove todos os itens do carrinho.
   */
  void LimparCarrinho();  

  /**
   * @brief Encerra esse pedido, quando o cliente já pagou pelos itens.
  */
  void Encerrar();

  /**
   * @brief Retorna o estado atual do pedido.
  */
  bool EstaEncerrado();

  /**
   * @brief Seta o status do carrinho.
  */
  void SetStatus(bool status);

  /**
   * @brief Retorna o id do cliente.
  */
  int GetIdCliente();

  /**
   * @brief Retorna se um desconto foi ou não aplicado.
  */
  bool GetDescontoAplicado();
};

#endif