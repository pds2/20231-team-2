#ifndef REMOCAO_SERVICO_HPP
#define REMOCAO_SERVICO_HPP

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
 * @brief Classe responsável por remover usuários no sistema.
 */
class RemocaoServico 
{
    private:
        ClienteRepositorio *_clienteRepositorio;
        RestauranteRepositorio *_restauranteRepositorio;

        /**
         * @brief Responsável por deletar um restaurante e suas dependências do sistema.
         * @param restaurante restaurante que será deletado.
        */
        void DeletarRestaurante(Restaurante* restaurante);

        /**
         * @brief Responsável por deletar um cliente e suas dependências do sistema.
         * @param cliente cliente que será deletado.
        */
        void DeletarCliente(Cliente* cliente);

    public:
        /**
         * @brief Construtor padrão.
         */
        RemocaoServico(DatabaseManager *dbManager);

        /**
         * @brief Função que deleta o usuário atual do sistema.
         * @param usuario usuário logado.
         */
        Usuario* RemoverUsuarioAtual(Usuario* usuario);
};

#endif