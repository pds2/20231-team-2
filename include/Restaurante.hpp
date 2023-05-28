#pragma once

#ifndef RESTAURANTE_HPP
#define RESTAURANTE_HPP

#include <string>

#include "Usuario.hpp"

/*
 *  Essa classe é responsável por armazenar e inicializar as informações básicas
 *  de um usuário do tipo restaurante.
 */
class Restaurante : public Usuario {
    private:
        std::string _CNPJ;
    public:
        /*
         * @brief Instância de um novo restaurante.
         */
        Restaurante(std::string nome, std::string login, std::string senha,std::string CNPJ);

        /*
         * @brief Retorna o CNPJ de um restaurante.
         */
       std::string GetCNPJ();
};

#endif