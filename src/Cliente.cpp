#include <string>

#include "../include/Cliente.hpp"

Cliente::Cliente(std::string nome, std::string login, std::string senha, std::string CPF):Usuario(nome, login, senha), _CPF(CPF){}

std::string Cliente::GetCPF(){
    return _CPF;
};