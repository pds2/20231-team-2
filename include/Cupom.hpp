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
    //pode ser definido mais tarde
    std::string _dataExpiracao;

public:
    /**
     * @brief Construtor da classe Cupom.
     * @param codigo O código do cupom.
     * @param desconto O valor do desconto em porcentagem.
     */
    Cupom(std::string codigo, double desconto);

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
     * @brief Retorna a data de expiração do cupom.
     * @return A data de expiração do cupom.
     */
    std::string GetDataDeExpiracao();

    /**
     * @brief Verifica se o cupom está válido.
     * @return true se o cupom estiver válido, false caso contrário.
     */
    bool EstaValido();

    /**
     * @brief Define o status do cupom como válido.
     */
    void SetaValido();
};

#endif // CUPOM_HPP
