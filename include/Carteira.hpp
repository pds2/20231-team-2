#ifndef CARTEIRA_HPP
#define CARTEIRA_HPP

#include <string>

/*
 * @brief Essa classe representa uma exceção que será lançada quando
 * um saldo negativo ou igual a zero tentar ser adicionado.
 */
class impossivel_adicionar_saldo_negativo_ou_igual_a_zero_e {};

/*
 * @brief Essa classe representa uma exceção que será lançada quando
 * um saldo negativo ou igual a zero tentar ser removido.
 */
class impossivel_remover_saldo_negativo_ou_igual_a_zero_e {};

/*
 * @brief Essa classe representa uma exceção que será lançada quando
 * um saldo maior que o saldo do cliente tentar ser removido.
 */
class saldo_insuficiente_para_remocao_e {};

/*
 * @brief Essa classe representa uma carteira que armazenará um saldo. É por ela
 * que o cliente terá o dinheiro para fazer compras.
 */
class Carteira{
  private:
  std::string _nomeDoCliente;
  double _saldo;

  public:
  /*
   * @brief Instancia uma carteira do Cliente, com saldo inicial
   * igual a 0.
   */
  Carteira(std::string nomeDoCliente);

  /*
   * @brief Retorna o Nome do Cliente.
   */
  std::string get_nome();

  /*
   * @brief Retorna o saldo do Cliente.
   */
  double get_saldo();

  /*
   * @brief Adiciona um determinado saldo da carteira.
   */
  void adicionar_saldo(double saldo);

  /*
   * @brief Remove um determinado saldo da carteira.
   */
  void remover_saldo(double saldo);
}
#endif