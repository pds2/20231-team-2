#include "../include/CupomBasico.hpp"

CupomBasico::CupomBasico(std::string etiqueta, double desconto, int idCliente) : Cupom(etiqueta, desconto, idCliente) {};

std::string CupomBasico::Descricao(){
    
    std::ostringstream oss;

    oss << "Você recebeu um desconto de ";
    oss << _valor_desconto * 100;
    oss << "%! Aproveite!";

    std::string descricao = oss.str();

    return descricao;
}