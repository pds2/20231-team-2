#ifndef CUPOMSERVICO_HPP
#define CUPOMSERVICO_HPP

#include <string>
#include <iostream>

#include "EntidadeBase.hpp"
#include "Cupom.hpp"
#include "Cliente.hpp"
#include "../Repositories/DatabaseManager.hpp"
#include "../Repositories/ClienteRepositorio.hpp"
#include "../Repositories/RestauranteRepositorio.hpp"


class CupomServico{

    private:
        ClienteRepositorio* _clienteRepositorio;
    public:
        /**
         * @brief Construtor padrão.
         * @param dbManager Um ponteiro para o Database.
         */
        CupomServico(DatabaseManager *dbManager);

        /**
         * @brief Função em que o cliente irá escolher a ação que ele deseja realizar.
         * @param cliente Um ponteiro para o cliente.
         */
        void escolherAcaoCliente(Cliente *cliente);

        /**
        * @brief Função que lista todos os cupons disponíveis para a compra de um cliente.
        * @param cliente Um ponteiro para o cliente.
        */
        void listarCupomDoCliente(Cliente *cliente);
};

#endif