#include <regex>
#include <string>

#include "Restaurante.hpp"

Restaurante::Restaurante(std::string nome, std::string login, std::string senha, std::string CNPJ)
    :Usuario(nome, login, senha, CNPJ ,TipoUsuario::RESTAURANTE)
{
    SetDocumento(CNPJ);
}

void Restaurante::AdicionarItem(Item* novoItem)
{
    for(Item* item : _itens)
    {
        if (item->GetId() == novoItem->GetId())
            return;
    }

    _itens.push_back(novoItem);
}

void Restaurante::RemoverItem(Item* alvo)
{
    for (auto it = _itens.begin(); it != _itens.end(); ++it)
    {
        if ((*it)->GetId() == alvo->GetId())
        {
            _itens.erase(it);
            break;
        }
    }
}

std::vector<Item*> Restaurante::GetItens()
{
    return _itens;
}

TipoUsuario Restaurante::GetTipo()
{
    return _tipo;
}

bool Restaurante::DocumentoValido(std::string documento)
{
    std::string cnpjLimpo = "";
    for (char c : documento) 
    {
        if (isdigit(c))
            cnpjLimpo += c;
    }

    if (cnpjLimpo.length() != 14)
        return false;

    if (!std::regex_match(cnpjLimpo, std::regex("\\d+"))) 
        return false;

    return true;
}

std::string Restaurante::FormatarDocumento(std::string documento)
{
    std::string cnpjLimpo = "";
    for (char c : documento) 
    {
        if (isdigit(c)) 
            cnpjLimpo += c;
    }

    std::string cnpjFormatado = "";
    
    for (int i = 0; i < 14; i++) {
        cnpjFormatado += cnpjLimpo[i];

        if (i == 1 || i == 4)
            cnpjFormatado += '.';
        if (i == 7)
            cnpjFormatado += '/';
        if (i == 11) 
            cnpjFormatado += '-';
    }

    return cnpjFormatado;
}