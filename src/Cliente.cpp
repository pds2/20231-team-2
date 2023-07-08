#include <string>

#include "Cliente.hpp"

Cliente::Cliente(std::string nome, std::string login, std::string senha, std::string CPF)
    :Usuario(nome, login, senha, TipoUsuario::CLIENTE), _CPF(CPF)
{
    _carteira = nullptr;
}

std::string Cliente::GetCPF(){
    return _CPF;
};

Carteira* Cliente::GetCarteira()
{
    return _carteira;
}

void Cliente::SetCarteira(Carteira* carteira)
{
    _carteira = carteira;
}


void Cliente::AdicionarCarrinho(Carrinho* carrinho)
{
    _carrinhos.push_back(carrinho);
}

void Cliente::RemoverCarrinho(Carrinho* carrinho)
{
    for (auto it = _carrinhos.begin(); it != _carrinhos.end(); ++it)
    {
        if ((*it)->GetId() == carrinho->GetId())
        {
            _carrinhos.erase(it);
            break;
        }
    }
}

std::vector<Carrinho*> Cliente::GetCarrinhos()
{
    return _carrinhos;
}

void Cliente::SetCarrinhos(std::vector<Carrinho*> carrinhos)
{
    _carrinhos = carrinhos;
}

TipoUsuario Cliente::GetTipo(){
    return _tipo;
}