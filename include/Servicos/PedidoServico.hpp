#ifndef PEDIDO_SERVICO_HPP
#define PEDIDO_SERVICO_HPP

#include <vector>
#include <map>
#include <string>

#include "../Repositories/DatabaseManager.hpp"
#include "../Repositories/ItemRepositorio.hpp"
#include "../Restaurante.hpp"
#include "../Usuario.hpp"
#include "../EntidadeBase.hpp"
#include "../Carrinho.hpp"


/*
 * @brief Essa classe é responsável por gerenciar
 * os pedidos feitos pelo usuário.
 */
class PedidoServico{
  private:
  std::map<int, Restaurante*> _Restaurantes;
  ItemRepositorio *_itemRepositorio;

  public:

  PedidoServico(DatabaseManager * dbManager);

  /*
   * @brief Esse método é um menu que apresenta as opções 
   * para o usuário interagir com o sistema.
   */
  void ImprimeMenu(Usuario *usuario);
  
  /*
   * @brief Esse método é responsável por Listar todos os
   * restaurantes disponíveis.
   */
  void ListarRestaurantes();

  /*
   * @brief Esse método é responsável por Listar todos os
   * itens de um restaurante.
   */
  void ListarItensDeUmRestaurante(int id);

  /*
   * @brief Esse metódo é responsável por criar um carrinho 
   * para o usuário. 
   */
  void EditarCarrinho(Carrinho *carrinho, int idDoItem, std::string AdicionarOuRemover);
};

#endif