#ifndef AUTENTICACAO_SERVICO_HPP
#define AUTENTICACAO_SERVICO_HPP

#include "Cliente.hpp"
#include "Restaurante.hpp"
#include "../Repositories/ClienteRepositorio.hpp"
#include "../Repositories/RestauranteRepositorio.hpp"

/**
 * Classe responsável por autenticar usuários no sistema.
*/
class AutenticacaoServico
{
    private:
        ClienteRepositorio* _clienteRepositorio;
        RestauranteRepositorio* _restauranteRepositorio;

        /**
         * @brief Busca um cliente ou restaurante com base no tipo do template.
         * @param login Login do usuário buscado.
         * @returns Um ponteiro pro usuário.
        */
        template<typename Tipo>
        Usuario* BuscaUsuario(std::string login);

        /**
         * @brief Login genérico para clientes e restaurantes.
         * @param buscador Ponteiro para função de busca dos usuários.
         * @param mensagem_sucesso mensagem adicionada no caso de sucesso de login.
        */
        template<typename Tipo>
        Tipo* LoginGenerico(std::string mensagem_sucesso);

        /**
         * @brief Interage com o usuário para validar uma senha.
         * @param usuario Um ponteiro pro usuário que está tentando fazer login.
         * @returns true caso a senha seja corrita.
        */
        bool SenhaValida(Usuario* usuario);

    public:
        /**
         * Responsável por inicializar essa classe.
         * @param clienteRepositorio Acesso aos clientes.
         * @param restauranteRepositorio Acesso aos restaurantes.
        */
        AutenticacaoServico(ClienteRepositorio* clienteRepositorio, RestauranteRepositorio* restauranteRepositorio);

        /**
         * Responsável por fazer o procedimento de login de um cliente.
         * @returns Um ponteiro para o cliente em caso de sucesso.
        */
        Cliente* LoginCliente();

        /**
         * Responsável por fazer o procedimento de login de um restaurante.
         * @returns Um ponteiro para o restaurante em caso de sucesso.
        */
        Restaurante* LoginRestaurante();
};

#endif