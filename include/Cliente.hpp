#pragma once

#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>

#include "Usuario.hpp"
#include "Carteira.hpp"

/*
 *  Essa classe é responsável por armazenar e inicializar as informações básicas
 *  de um usuário do tipo cliente.
 */
class Cliente : public Usuario {
    private:
        std::string _CPF;
        Carteira* _carteira;
    public:
        /**
         * @brief Instância de um novo cliente.
         */
        Cliente(std::string nome, std::string login, std::string senha, std::string CPF);

        /**
         * @brief Retorna o CPF de um cliente.
         */
        std::string GetCPF();

        /**
         * @brief Retorna um ponteiro pra carteira desse cliente.
         */
        Carteira* GetCarteira();

        /**
         * @brief Seta o ponteiro pra carteira desse cliente.
         */
        void SetCarteira(Carteira* carteira);
};

#endif