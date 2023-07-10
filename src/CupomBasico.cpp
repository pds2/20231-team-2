#include "../include/CupomBasico.hpp"

CupomBasico::CupomBasico(std::string etiqueta, double desconto, int idCliente) : Cupom(etiqueta, desconto, idCliente, CupomType::BASICO) {};

std::string CupomBasico::Descricao(){
    
    std::ostringstream oss;

    oss << "Você recebeu um desconto de ";
    oss << _valor_desconto;
    oss << "%! Aproveite!";

    std::string descricao = oss.str();

    return descricao;
}