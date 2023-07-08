#pragma once

#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>

#include "Usuario.hpp"
#include "Carteira.hpp"
#include "Carrinho.hpp"

/*
 *  Essa classe é responsável por armazenar e inicializar as informações básicas
 *  de um usuário do tipo cliente.
 */
class Cliente : public Usuario {
    private:
        std::string _CPF;
        Carteira* _carteira;
        std::vector<Carrinho*> _carrinhos;
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

        /**
         * @brief Adiciona um carrinho a esse cliente.
        */
        void AdicionarCarrinho(Carrinho* carrinho);

        /**
         * @brief Remover um carrinho desse cliente.
        */
        void RemoverCarrinho(Carrinho* carrinho);

        /**
         * @brief Retorna os carrinhos desse cliente.
        */
        std::vector<Carrinho*> GetCarrinhos();

        /**
         * @brief Substitui o vector de carrinhos desse cliente.
         * @param carrinhos Novos dados.
        */
        void SetCarrinhos(std::vector<Carrinho*> carrinhos);

        /**
         * @brief Retorna o tipo de um usário, neste caso, cliente.
         */
        TipoUsuario GetTipo() override;
};

#endif