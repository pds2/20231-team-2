#ifndef CUPOMCUSTOMIZADO_HPP
#define CUPOMCUSTOMIZADO_HPP

#include "Cupom.hpp"

/**
 * @class CupomCustomizado
 * @brief Classe que representa um cupom de desconto que já vem com etiqueta e mensagem padrões do sistema, isto é,
 *  não permite customização de etiqueta nem mensagem.
 * 
 * Essa classe representa um cupom que pode ser utilizado para fornecer descontos aos clientes em suas compras.
 */
class CupomCustomizado : public Cupom{

    public:
        CupomCustomizado(std::string etiqueta, double desconto, int idCliente, std::string descricao);
        virtual std::string Descricao() override;

};

#endif