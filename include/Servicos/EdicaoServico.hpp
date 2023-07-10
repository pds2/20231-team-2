#ifndef EDICAO_SERVICO_HPP
#define EDICAO_SERVICO_HPP

#include <string>
#include <iostream>

#include "Usuario.hpp"
#include "Cliente.hpp"
#include "Restaurante.hpp"
#include "EntidadeBase.hpp"

#include "Repositories/DatabaseManager.hpp"
#include "Repositories/ClienteRepositorio.hpp"
#include "Repositories/RestauranteRepositorio.hpp"

/**
 * @brief Classe responsável por editar usuários no sistema.
 */
class EdicaoServico 
{
    private:
        ClienteRepositorio *_clienteRepositorio;
        RestauranteRepositorio *_restauranteRepositorio;

        /**
         * @brief Responsável por editar um restaurante e suas dependências do sistema.
         * @param restaurante restaurante que será editado.
        */
        void AtualizarRestaurante(Restaurante* restaurante);

        /**
         * @brief Responsável por editar um cliente e suas dependências do sistema.
         * @param cliente cliente que será editado.
        */
        void AtualizarCliente(Cliente* cliente);

    public:
        /**
         * @brief Construtor padrão.
         */
        EdicaoServico(DatabaseManager *dbManager);

        /**
         * @brief Função que edita o usuário atual do sistema.
         * @param usuario usuário logado.
         */
        void EditarUsuarioAtual(Usuario* usuario);
};

#endif