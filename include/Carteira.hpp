#pragma once

#ifndef CARTEIRA_HPP
#define CARTEIRA_HPP

#include <string>
#include "EntidadeBase.hpp"

/**
 * @class impossivel_adicionar_saldo_negativo_ou_igual_a_zero_e
 * @brief Exceção lançada quando se tenta adicionar um saldo negativo ou igual a zero à carteira.
 */
class impossivel_adicionar_saldo_negativo_ou_igual_a_zero_e {};

/**
 * @class impossivel_remover_saldo_negativo_ou_igual_a_zero_e
 * @brief Exceção lançada quando se tenta remover um saldo negativo ou igual a zero da carteira.
 */
class impossivel_remover_saldo_negativo_ou_igual_a_zero_e {};

/**
 * @class saldo_insuficiente_para_remocao_e
 * @brief Exceção lançada quando se tenta remover um saldo maior do que o saldo disponível na carteira.
 */
class saldo_insuficiente_para_remocao_e {};

/**
 * @class sem_saldo_e
 * @brief Exceção lançada quando se tenta remover saldo de uma carteira com saldo igual a zero.
 */
class sem_saldo_e {};

/**
 * @class Carteira
 * @brief Classe que representa uma carteira do cliente.
 *
 * Essa classe representa uma carteira que armazena o saldo do cliente, utilizado para fazer compras.
 */
class Carteira : public EntidadeBase {
private:
    int _idCliente;
    double _saldo;

public:
    /**
     * @brief Construtor da classe Carteira (o saldo inicial é 0.0).
     * @param idCliente O identificador do cliente no banco.
     */
    Carteira(int idCliente);

    /**
     * @brief Retorna o ID do cliente associado à carteira.
     * @return O ID do cliente.
     */
    int GetIdCliente();

    /**
     * @brief Retorna o saldo atual da carteira.
     * @return O saldo da carteira.
     */
    double GetSaldo();

    /**
     * @brief Define o saldo da carteira.
     * @param saldo O saldo a ser definido.
     */
    void SetSaldo(double saldo);

    /**
     * @brief Adiciona um valor ao saldo da carteira.
     * @param saldo O valor a ser adicionado.
     */
    void AdicionarSaldo(double saldo);

    /**
     * @brief Remove um valor do saldo da carteira.
     * @param saldo O valor a ser removido.
     */
    void RemoverSaldo(double saldo);

    /**
     * @brief Altera o id do cliente dono dessa carteira.
     * @param id id do cliente;
    */
    void SetIdCliente(int id);
};

#endif // CARTEIRA_HPP
