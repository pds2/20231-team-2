#include <string>

#include "../include/Cliente.hpp"

Cliente::Cliente(std::string nome, std::string login, std::string senha, std::string CPF)
    :Usuario(nome, login, senha, TipoUsuario::CLIENTE), _CPF(CPF)
{}

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