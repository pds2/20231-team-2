#include <string>

#include "../include/Usuario.hpp"

//considerando o id como 1, pois ainda não temos integração com banco de dados.
Usuario::Usuario(std::string nome, std::string login, std::string senha):EntidadeBase(1), _nome(nome), _login(login), _senha(senha) {}

std::string Usuario::GetLogin(){
    return _login;
};

std::string Usuario::GetSenha(){
    return _senha;
};


std::string Usuario::GetNome(){
    return _nome;
};