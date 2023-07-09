#include <string>

#include "Usuario.hpp"

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

void Usuario::SetSenha(std::string senha)
{
    _senha = senha;
}

std::string Usuario::GetNome()
{
    return _nome;
};