#include <string>

#include "Usuario.hpp"

Usuario::Usuario(std::string nome, std::string login, std::string senha, std::string documento, TipoUsuario tipo)
    : _nome(nome), _login(login), _senha(senha), _documento(documento), _tipo(tipo)
{   }

std::string Usuario::GetLogin()
{
    return _login;
};

void Usuario::SetLogin(std::string login)
{
    _login = login;
}

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

void Usuario::SetNome(std::string nome)
{
    _nome = nome;
}

std::string Usuario::GetDocumento()
{
    return _documento;
}

void Usuario::SetDocumento(std::string documento)
{
    if (!DocumentoValido(documento))
        throw documento_invalido_e();

    _documento = FormatarDocumento(documento);
}