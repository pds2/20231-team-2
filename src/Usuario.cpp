#include <string>

#include "../include/Usuario.hpp"

Usuario::Usuario(std::string nome, std::string login, std::string senha): _nome(nome), _login(login), _senha(senha) {}

std::string Usuario::GetLogin(){
    return _login;
};

std::string Usuario::GetSenha(){
    return _senha;
};


std::string Usuario::GetNome(){
    return _nome;
};