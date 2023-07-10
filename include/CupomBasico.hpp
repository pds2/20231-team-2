#ifndef CUPOMBASICO_HPP
#define CUPOMBASICO_HPP

#include "Cupom.hpp"

/**
 * @class CupomBasico
 * @brief Classe que representa um cupom de desconto que já vem com etiqueta e mensagem padrões do sistema, isto é,
 *  não permite customização de etiqueta nem mensagem.
 * 
 * Essa classe representa um cupom que pode ser utilizado para fornecer descontos aos clientes em suas compras.
 */
class CupomBasico : public Cupom{

    public:
        CupomBasico(std::string etiqueta, double desconto, int idCliente);
        virtual std::string Descricao() override;
};

#endif