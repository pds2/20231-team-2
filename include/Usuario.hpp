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

/**
 * @class Usuario
 * @brief Classe base para entidades de usuário.
 *
 * Essa classe é responsável por armazenar e inicializar as informações básicas
 * comuns às entidades de Usuário, como cliente e restaurante.
 */
class Usuario : public EntidadeBase
{
protected:
    std::string _nome;
    std::string _login;
    std::string _senha;
    TipoUsuario _tipo;

public:
    /**
     * @brief Construtor da classe Usuario.
     * @param nome O nome do usuário.
     * @param login O login do usuário.
     * @param senha A senha do usuário.
     * @param tipo O tipo do usuário.
     */
    Usuario(std::string nome, std::string login, std::string senha, TipoUsuario tipo);

    /**
     * @brief Retorna o login do usuário.
     * @return O login do usuário.
     */
    std::string GetLogin();

    /**
     * @brief Retorna a senha do usuário.
     * @return A senha do usuário.
     */
    std::string GetSenha();

    /**
     * @brief Retorna o nome do usuário.
     * @return O nome do usuário.
     */
    std::string GetNome();

    /**
     * @brief Método virtual que retorna o tipo do usuário.
     * @return O tipo do usuário.
     */
    virtual TipoUsuario GetTipo() = 0;
};

#endif // USUARIO_HPP
