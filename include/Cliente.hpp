#pragma once

#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>

#include "Usuario.hpp"

/*
 *  Essa classe é responsável por armazenar e inicializar as informações básicas
 *  de um usuário do tipo cliente.
 */
class Cliente : public Usuario {
    private:
        std::string _CPF;
        //um cliente deve possuir uma carteira(olhar com Gabriel)
    public:
        /*
         * @brief Instância de um novo cliente.
         */
        Cliente(std::string CPF);

        /*
         * @brief Retorna o CPF de um usuário.
         */
       std::string GetCPF();
};

#endif