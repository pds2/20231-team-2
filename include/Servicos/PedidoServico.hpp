#ifndef PEDIDO_SERVICO_HPP
#define PEDIDO_SERVICO_HPP

#include <vector>
#include <map>
#include <string>

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
  std::map<int, Restaurante*> _Restaurantes;
  ItemRepositorio *_itemRepositorio;
  CarrinhoRepositorio *_carrinhoRepositorio;
  CarteiraRepositorio *_carteiraRepositorio;

  public:

  PedidoServico(DatabaseManager * dbManager);

  /**
   * @brief Esse método é um menu que apresenta as opções 
   * para o usuário interagir com o sistema.
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
   */
  void ListarItensDeUmRestaurante(int id);

  /**
   * @brief Esse metódo é responsável por criar um carrinho 
   * para o usuário. O usuário pode adicionar e remover itens
   * com esse método
   */
  void EditarCarrinho(Carrinho *carrinho, int idDoItem, std::string AdicionarOuRemover);

  /**
   * @brief Esse metódo é responsável por remover todos os itens
   * do carrinho do usuário
   */
  void LimparCarrinho(Carrinho *carrinho);

  /**
   * @brief Esse metódo é responsável por finalizar o carrinho de compras
   * do usuário quando ele estiver pronto para pagar.
   */
  void EncerrarCarrinho(Carrinho *carrinho, Cliente *cliente);
};

#endif