#include "../include/CupomCustomizado.hpp"

CupomCustomizado::CupomCustomizado(std::string etiqueta, double desconto, int idCliente, std::string descricao) :
    Cupom(etiqueta, desconto, idCliente, CupomType::CUSTOMIZADO)
{
    if(descricao == ""){
        throw impossivel_descricao_vazia_e();
    }

    _descricao = descricao;
};

std::string CupomCustomizado::Descricao(){
    return _descricao;
}