#include <string>
#include "Item.hpp"

Item::Item(std::string nome, std::string descricao, ItemType tipo, double precoBase, int idRestaurante)
{
    _nome = nome;
    _descricao = descricao;
    _tipo = tipo;
    
    _precoBase = precoBase;
    _precoComDesconto = precoBase;

    _idRestaurante = idRestaurante;
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
    return (ExisteUmDescontoAplicado()) ? _precoComDesconto : _precoBase;
}

bool Item::ExisteUmDescontoAplicado()
{
    return _precoBase != _precoComDesconto;
}

void Item::AplicarDesconto(int percentualDesconto)
{
    if (percentualDesconto <= 0 || percentualDesconto > 100)
        throw desconto_invalido_e();

    _precoComDesconto = (_precoBase/100) * (100 - percentualDesconto);
}

void Item::RemoverDescontoAtual()
{
    if (!ExisteUmDescontoAplicado())
        return;

    _precoComDesconto = _precoBase;
}

void Item::SetPrecoComDesconto(double precoComDesconto)
{
    _precoComDesconto = precoComDesconto;
}

int Item::GetIdRestaurante()
{
    return _idRestaurante;
}