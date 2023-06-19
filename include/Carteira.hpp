#ifndef CARTEIRA_HPP
#define CARTEIRA_HPP

#include <string>
#include "EntidadeBase.hpp"

/**
 * @brief Essa classe representa uma exceção que será lançada quando
 * um saldo negativo ou igual a zero tentar ser adicionado.
 */
class impossivel_adicionar_saldo_negativo_ou_igual_a_zero_e {};

/**
 * @brief Essa classe representa uma exceção que será lançada quando
 * um saldo negativo ou igual a zero tentar ser removido.
 */
class impossivel_remover_saldo_negativo_ou_igual_a_zero_e {};

/**
 * @brief Essa classe representa uma exceção que será lançada quando
 * um saldo maior que o saldo do cliente tentar ser removido.
 */
class saldo_insuficiente_para_remocao_e {};

/**
 * @brief Essa classe representa uma exceção que será lançada quando
 * o cliente tentar remover saldo com saldo igual a 0.
 */
class sem_saldo_e {};

/**
 * @brief Essa classe representa uma carteira que armazenará um saldo. É por ela
 * que o cliente terá o dinheiro para fazer compras.
 */
class Carteira
  : public EntidadeBase
{
  private:
    int _idCliente;
    double _saldo;

  public:
    /**
     * @brief Instancia uma carteira do Cliente, com saldo inicial
     * igual a 0.
     */
    Carteira(int idCliente);

    /**
     * @brief Retorna o id do Cliente.
     */
    int GetIdCliente();

    /**
     * @brief Retorna o saldo do Cliente.
     */
    double GetSaldo();

    /**
     * @brief Seta o saldo do cliente.
    */
    void SetSaldo(double saldo);

    /**
     * @brief Adiciona um determinado saldo da carteira.
     */
    void AdicionarSaldo(double saldo);

    /**
     * @brief Remove um determinado saldo da carteira.
     */
    void RemoverSaldo(double saldo);
};

#endif