#pragma once

#ifndef CUPOM_HPP
#define CUPOM_HPP

#include <string>
#include "EntidadeBase.hpp"

/**
 * @class Cupom
 * @brief Classe que representa um cupom de desconto.
 *
 * Essa classe representa um cupom que pode ser utilizado para fornecer descontos aos clientes em suas compras.
 */
class Cupom : public EntidadeBase {
private:
    std::string _codigo;
    double _desconto;
    bool _valido;
    int _idDoCliente;
    

public:
    /**
     * @brief Construtor da classe Cupom.
     * @param codigo O código do cupom.
     * @param desconto O valor do desconto em porcentagem.
     * @param idDoCliente O id do cliente que tem esse cupom.
     */
    Cupom(std::string codigo, double desconto, int idDoCliente);

    /**
     * @brief Retorna o código do cupom.
     * @return O código do cupom.
     */
    std::string GetCodigo();

    /**
     * @brief Retorna o valor do desconto do cupom.
     * @return O valor do desconto em porcentagem.
     */
    double GetValor();

    /**
     * @brief Verifica se o cupom está válido.
     * @return true se o cupom estiver válido, false caso contrário.
     */
    bool EstaValido();

    /**
     * @brief Define o status do cupom como válido.
     */
    void SetaValido();

    /**
     * @brief REtorna o id do cliente.
     * @return O id do cliente.
     */
    int GetIdDoCliente();
};

#endif // CUPOM_HPP
