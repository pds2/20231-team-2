#include "../include/CupomCustomizado.hpp"

CupomCustomizado::CupomCustomizado(std::string etiqueta, double desconto, int idCliente, std::string descricao) :
    Cupom(etiqueta, desconto, idCliente),
    _descricao(descricao) 
{};

std::string CupomCustomizado::Descricao(){
    return _descricao;
}