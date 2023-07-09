#ifndef CADASTRO_SERVICO_HPP
#define CADASTRO_SERVICO_HPP

#include <string>
#include <iostream>

#include "../Cliente.hpp"
#include "../EntidadeBase.hpp"
#include "../Repositories/ClienteRepositorio.hpp"
#include "../Repositories/DatabaseManager.hpp"
#include "../Repositories/RestauranteRepositorio.hpp"
#include "../Restaurante.hpp"
#include "../Usuario.hpp"

/**
 * @brief Classe responsável por cadastrar usuários no sistema.
 */
class CadastroServico {
private:
  ClienteRepositorio *_clienteRepositorio;
  RestauranteRepositorio *_restauranteRepositorio;

public:
  /**
  * @brief Construtor padrão.
  */
  CadastroServico(DatabaseManager *dbManager);

  /**
  * @brief Função em que o usuário irá escolher se ele deseja se cadastrar no sistema como um cliente ou como um restaurante.
  */
  Usuario* MenuCadastro();

  /**
  * @brief Cadastra um usuário do tipo cliente no sistema e inicializa a carteira dele.
  * @param nome Uma string que representa o nome do cliente.
  * @param cpf Uma string que representa o cpf do cliente.
  * @param login Uma string que representa o login do cliente para que ele acesse sua conta.
  * @param senha Uma string que representa a senha do cliente para que ele acesse sua conta.
  */
  Cliente* CadastrarCliente(std::string& nome, std::string& cpf, std::string& login, std::string& senha);

  /**
  * @brief Cadastra um usuário do tipo restaurante no sistema.
  * @param nome Uma string que representa o nome do restaurante.
  * @param cnpj Uma string que representa o cnpj do restaurante.
  * @param login Uma string que representa o login do restaurante para que ele acesse sua conta.
  * @param senha Uma string que representa a senha do restaurante para que ele acesse sua conta.
  */
  Restaurante* CadastrarRestaurante(std::string& nome, std::string& cnpj, std::string& login, std::string& senha);
};

#endif