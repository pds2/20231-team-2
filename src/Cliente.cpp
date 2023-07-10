#include <string>

#include "Cliente.hpp"
#include "Usuario.hpp"
#include "Carteira.hpp"
#include "Carrinho.hpp"
#include "Cupom.hpp"
#include "Utils/ValidadorDeDocumentos.hpp"

Cliente::Cliente(std::string nome, std::string login, std::string senha, std::string CPF)
    :Usuario(nome, login, senha, CPF, TipoUsuario::CLIENTE)
{   
    SetDocumento(CPF);
}

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

TipoUsuario Cliente::GetTipo()
{
    return _tipo;
}

void Cliente::AdicionaCupom(Cupom* cupom)
{
    _cupons.push_back(cupom);
}

std::vector<Cupom*> Cliente::GetCupons()
{
    return _cupons;
}

void Cliente::SetCupons(std::vector<Cupom*> cupons)
{
    _cupons = cupons;
}

Cupom* Cliente::GetCupom(int id)
{
    for(auto it : _cupons)
    {
        if(it->GetId() == id)
            return it;
    }

    throw cupom_nao_existe_e();
}

bool Cliente::DocumentoValido(std::string documento)
{
    return ValidadorDeDocumentos::ValidarCPF(documento);
}

std::string Cliente::FormatarDocumento(std::string documento)
{
    std::string cpfLimpo = "";
    for (char c : documento) 
    {
        if (isdigit(c)) 
            cpfLimpo += c;
    }

    std::string cpfFormatado = "";

    for (int i = 0; i < 11; i++) 
    {
        cpfFormatado += cpfLimpo[i];

        if (i == 2 || i == 5)
            cpfFormatado += '.';
        if (i == 8) 
            cpfFormatado += '-';
    }

    return cpfFormatado;
}