#ifndef CARTEIRA_SERVICO_HPP
#define CARTEIRA_SERVICO_HPP

#include <string>
#include <iostream>

#include "../Cliente.hpp"
#include "../Carteira.hpp"
#include "../EntidadeBase.hpp"
#include "../Repositories/ClienteRepositorio.hpp"
#include "../Repositories/DatabaseManager.hpp"
#include "../Repositories/CarteiraRepositorio.hpp"
#include "../Usuario.hpp"

/*
 * @brief Classe responsável pelo gerenciamento por parte do cliente com a sua carteira.
 */
class CarteiraServico {
private:
  ClienteRepositorio *_clienteRepositorio;
  CarteiraRepositorio *_carteiraRepositorio;

public:
  /*
  * @brief Construtor padrão.
  */
  CarteiraServico(DatabaseManager *dbManager);

  /*
  * @brief Função em que o cliente irá escolher a ação que ele deseja realizar.
  */
  void escolherAcao(Usuario *usuario);

  /*
  * @brief Função em que o saldo do cliente será impresso.
  */
  void imprimeSaldo(Usuario *usuario);

  /*
  * @brief Função em que o cliente adiciona saldo na sua carteira e o saldo antigo e o novo são impressos.
  */
  void adicionaSaldo(Usuario *usuario);

  
};

#endif