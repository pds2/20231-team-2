#pragma once

#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include "EntidadeBase.hpp"

/**
 * @brief Exceção lançada quando um login não é encontrado.
*/
class login_nao_encontrado_e {};

/**
 * @enum TipoUsuario
 * Um enumerador representando os tipos de usuários disponíveis.
 */
enum class TipoUsuario
{
    RESTAURANTE,
    CLIENTE
};

/*
 *  Essa classe é responsável por armazenar e inicializar as informações básicas
 * comuns às entidades de Usuário, como cliente e restaurante. 
 */
class Usuario 
: public EntidadeBase
{
    protected:
        std::string _nome;
        std::string _login;
        std::string _senha;
        TipoUsuario _tipo;
    public:
        /**
         * @brief Instância de um novo usuário.
         */
        Usuario(std::string nome, std::string login, std::string senha, TipoUsuario tipo);

        /**
         * @brief Retorna o login de um usuário.
         */
       std::string GetLogin();

        /**
         * @brief Retorna a senha de um usário.
         */
        std::string GetSenha();

        /**
         * @brief Retorna o nome de um usário.
         */
        std::string GetNome();

        /**
         * @brief Retorna o tipo de um usário.
         */
        TipoUsuario GetTipo();
};

#endif