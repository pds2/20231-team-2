#include <string>

#include "../include/Restaurante.hpp"

Restaurante::Restaurante(std::string nome, std::string login, std::string senha, std::string CNPJ):Usuario(nome, login, senha), _CNPJ(CNPJ){}

std::string Restaurante::GetCNPJ(){
    return _CNPJ;
};