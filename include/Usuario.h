#pragma once

#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

/*
 *  Essa classe é responsável por armazenar e inicializar as informações básicas
 * comuns às entidades de Usuário, como cliente e restaurante. 
 */
class Usuario
{
    private:
        std::string _login;
        std::string _senha;
    public:
        /*
         * @brief Instância de um novo usuário.
         */
        Usuario(std::string login, std::string senha);

        /*
         * @brief Retorna o login de um usuário.
         */
       std::string GetLogin();

        /*
         * @brief Retorna a senha de um usário.
         */
        std::string GetSenha();
};

#endif