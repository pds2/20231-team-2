#include <string>

#include "../include/Restaurante.hpp"

Restaurante::Restaurante(std::string nome, std::string login, std::string senha, std::string CNPJ)
    :Usuario(nome, login, senha), _CNPJ(CNPJ)
{}

std::string Restaurante::GetCNPJ()
{
    return _CNPJ;
};

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