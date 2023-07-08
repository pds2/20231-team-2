#pragma once

#ifndef RESTAURANTE_HPP
#define RESTAURANTE_HPP

#include <string>
#include <vector>

#include "Item.hpp"
#include "Usuario.hpp"

/**
 * @class Restaurante
 * @brief Classe que representa um restaurante.
 *
 * Essa classe é responsável por armazenar e inicializar as informações básicas
 * de um usuário do tipo restaurante.
 */
class Restaurante : public Usuario {
private:
    std::string _CNPJ;
    std::vector<Item*> _itens;

public:
    /**
     * @brief Construtor da classe Restaurante.
     * @param nome O nome do restaurante.
     * @param login O login do restaurante.
     * @param senha A senha do restaurante.
     * @param CNPJ O CNPJ do restaurante.
     */
    Restaurante(std::string nome, std::string login, std::string senha, std::string CNPJ);

    /**
     * @brief Retorna o CNPJ do restaurante.
     * @return O CNPJ do restaurante.
     */
    std::string GetCNPJ();

    /**
     * @brief Adiciona um item a esse restaurante.
     * @param item O item a ser adicionado.
     */
    void AdicionarItem(Item* item);

    /**
     * @brief Remove um item desse restaurante.
     * @param item O item a ser removido.
     */
    void RemoverItem(Item* item);

    /**
     * @brief Retorna os itens desse restaurante.
     * @return Um vetor de ponteiros para os itens do restaurante.
     */
    std::vector<Item*> GetItens();

    /**
     * @brief Retorna o tipo do usuário, neste caso, restaurante.
     * @return O tipo do usuário.
     */
    TipoUsuario GetTipo() override;
};

#endif // RESTAURANTE_HPP
