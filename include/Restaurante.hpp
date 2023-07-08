#pragma once

#ifndef RESTAURANTE_HPP
#define RESTAURANTE_HPP

#include <string>
#include <vector>

#include "Item.hpp"
#include "Usuario.hpp"

/*
 *  Essa classe é responsável por armazenar e inicializar as informações básicas
 *  de um usuário do tipo restaurante.
 */
class Restaurante : public Usuario {
    private:
        std::string _CNPJ;
        std::vector<Item*> _itens;
    public:
        /**
         * @brief Instância de um novo restaurante.
         */
        Restaurante(std::string nome, std::string login, std::string senha,std::string CNPJ);

        /**
         * @brief Retorna o CNPJ de um restaurante.
         */
        std::string GetCNPJ();

        /**
         * @brief Adiciona um item a esse restaurante.
        */
        void AdicionarItem(Item* item);

        /**
         * @brief Remove um item desse restaurante.
        */
        void RemoverItem(Item* item);

        /**
         * @brief Acesso aos itens desse restaurante;
         * @returns Um vector contendo ponteiros pros itens.
        */
        std::vector<Item*> GetItens();

        /**
         * @brief Retorna o tipo de um usário, neste caso, restaurante.
         */
        TipoUsuario GetTipo() override;
};

#endif