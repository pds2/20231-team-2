#include <string>
#include "../include/Item.hpp"

Item::Item(std::string nome, std::string descricao, ItemType tipo, double precoBase)
    : EntidadeBase(0)
{
    _nome = nome;
    _descricao = descricao;
    _tipo = tipo;
    
    _precoBase = precoBase;
    _precoComDesconto = precoBase;

    _descontoAplicado = false;
}

std::string Item::GetNome()
{
    return _nome;
}
 
std::string Item::GetDescricao()
{
    return _descricao;
}

ItemType Item::GetTipo()
{
    return _tipo;
}

double Item::GetPrecoBase()
{
    return _precoBase;
}

double Item::GetPrecoAtual()
{
    return (_descontoAplicado) ? _precoComDesconto : _precoBase;
}

bool Item::ExiteUmDescontoAplicado()
{
    return _descontoAplicado;
}

void Item::AplicarDesconto(int percentualDesconto)
{
    if (percentualDesconto <= 0 || percentualDesconto > 100)
        throw desconto_invalido_e();

    _descontoAplicado = true;
    _precoComDesconto = (_precoBase/100) * (100 - percentualDesconto);
}

void Item::RemoverDescontoAtual()
{
    if (!_descontoAplicado)
        return;

    _descontoAplicado = false;
    _precoComDesconto = _precoBase;
}