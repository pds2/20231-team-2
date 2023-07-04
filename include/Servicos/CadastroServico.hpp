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

/*
 * @brief Classe responsável por cadastrar usuários no sistema.
 */
class CadastroServico {
private:
  ClienteRepositorio *_clienteRepositorio;
  RestauranteRepositorio *_restauranteRepositorio;

public:
  CadastroServico(DatabaseManager *dbManager);
  void escolherTipoCadastro();
  void cadastrarCliente(std::string& nome, std::string& cpf, std::string& login, std::string& senha);
  void cadastrarRestaurante(std::string& nome, std::string& cnpj, std::string& login, std::string& senha);
};

#endif