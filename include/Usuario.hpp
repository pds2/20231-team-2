#pragma once

#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include "EntidadeBase.hpp"

/**
 * @class documento_invalido_e
 * @brief Exceção lançada quando um documento não está no formato correto.
 */
class documento_invalido_e {};

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
    std::string _documento;
    TipoUsuario _tipo;

public:
    /**
     * @brief Construtor da classe Usuario.
     * @param nome O nome do usuário.
     * @param login O login do usuário.
     * @param senha A senha do usuário.
     * @param documento Documento do cliente.
     * @param tipo O tipo do usuário.
     */
    Usuario(std::string nome, std::string login, std::string senha, std::string documento, TipoUsuario tipo);

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
     * @brief Altera a senha do usuário.
     * @param senha nova senha.
     */
    void SetSenha(std::string senha);

    /**
     * @brief Retorna o nome do usuário.
     * @return O nome do usuário.
     */
    std::string GetNome();

    /**
     * @brief Altera o documento do usuário.
     * @param documento Novo documento.
    */
    void SetDocumento(std::string documento);

    /**
     * @brief Retorna o documento do usuário.
     * @return O documento.
    */
    std::string GetDocumento();

    /**
     * @brief Método virtual que retorna o tipo do usuário.
     * @return O tipo do usuário.
     */
    virtual TipoUsuario GetTipo() = 0;

    /**
     * @brief Responsável por validar o formato de um documento informado.
     * @param documento Documento a ser validado.
     * @returns true caso sejá válido.
    */
    virtual bool DocumentoValido(std::string documento) = 0;

    /**
     * @brief Responsável por formatar o documento informado.
     * @param documento Documento a ser formatado.
     * @returns Documento com a formatação correta.
    */
    virtual std::string FormatarDocumento(std::string documento) = 0;
};

#endif // USUARIO_HPP
