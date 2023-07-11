#ifndef PEDIDO_SERVICO_HPP
#define PEDIDO_SERVICO_HPP

#include <vector>
#include <map>
#include <string>

#include "Repositories/RestauranteRepositorio.hpp"
#include "Repositories/CarteiraRepositorio.hpp"
#include "Repositories/CarrinhoRepositorio.hpp"
#include "Repositories/DatabaseManager.hpp"
#include "Repositories/ItemRepositorio.hpp"
#include "EntidadeBase.hpp"
#include "Restaurante.hpp"
#include "Carrinho.hpp"
#include "Usuario.hpp"

/**
 * @brief Essa classe é responsável por gerenciar
 * os pedidos feitos pelo usuário.
 */
class PedidoServico{
  private:
  RestauranteRepositorio* _RestaurantesRepositorio;
  ItemRepositorio *_itemRepositorio;
  CarrinhoRepositorio *_carrinhoRepositorio;
  CarteiraRepositorio *_carteiraRepositorio;
  CupomRepositorio *_cupomRepositorio;
  CupomServico *_cupom;

  public:

  /**
  * @brief Construtor padrão.
  * @param dbManager Um ponteiro para o Database.
  */
  PedidoServico(DatabaseManager *dbManager, CupomServico *cupom);

  /**
   * @brief Esse método é um menu que apresenta as opções 
   * para o usuário interagir com o sistema.
   * @param cliente Um ponteiro para o cliente que acessa o menu.
   */
  void ImprimeMenu(Cliente *cliente);
  
  /**
   * @brief Esse método é responsável por Listar todos os
   * restaurantes disponíveis.
   */
  void ListarRestaurantes();

  /**
   * @brief Esse método é responsável por Listar todos os
   * itens de um restaurante.
   * @param id O id do restaurante.
   */
  void ListarItensDeUmRestaurante(int id);

  /**
   * @brief Esse metódo é responsável por criar um carrinho 
   * para o usuário. O usuário pode adicionar e remover itens
   * com esse método.
   * @param carrinho Um ponteiro para o carrinho do cliente.
   * @param idDoItem O id do item que será adicionado ou removido.
   * @param AdicionarouRemover Uma string que indica se o cliente irá
   * adicionar ou remover um item.
   */
  void EditarCarrinho(Carrinho *carrinho, int idDoItem, std::string AdicionarOuRemover);

  /**
   * @brief Esse metódo é responsável por remover todos os itens
   * do carrinho do usuário.
   * @param carrinho Um ponteiro para o carrinho do cliente.
   */
  void LimparCarrinho(Carrinho *carrinho);

  /**
   * @brief Esse metódo é responsável por finalizar o carrinho de compras
   * do usuário quando ele estiver pronto para pagar.
   * @param carrinho Um ponteiro para o carrinho do cliente.
   * @param cliente Um ponteiro para o cliente.
   */
  void EncerrarCarrinho(Carrinho *carrinho, Cliente *cliente);
  
  /**
   * @brief Esse metódo é responsável por finalizar o carrinho de compras
   * do usuário quando ele estiver pronto para pagar.
   * @param AdicionarouRemover Uma string que indica se o cliente irá aplicar ou não um cupom.
   * @param cliente Um ponteiro para o cliente.
   * @param carrinho Um ponteiro para o carrinho do cliente.
   */
  void AplicaCupom(std::string &aplicarCupom, Cliente *cliente, Carrinho *carrinho);

  /**
   * @brief Esse metódo é responsável por imprimir um menu do carrinho de compras
   * do cliente.
  */
  void MenuDoCarrinho(Cliente *cliente);
};

#endif