#include <string>

#include "../include/Usuario.hpp"

Usuario::Usuario(std::string nome, std::string login, std::string senha, TipoUsuario tipo)
    : _nome(nome), _login(login), _senha(senha), _tipo(tipo)
{   }

std::string Usuario::GetLogin()
{
    return _login;
};

std::string Usuario::GetSenha()
{
    return _senha;
};

std::string Usuario::GetNome()
{
    return _nome;
};

TipoUsuario Usuario::GetTipo()
{
    return _tipo;
}