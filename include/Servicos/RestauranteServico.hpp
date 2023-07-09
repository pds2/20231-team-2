#pragma once

#ifndef RESTAURANTE_SERVICO_HPP
#define RESTAURANTE_SERVICO_HPP

#include <string>
#include <iostream>

#include "Restaurante.hpp"
#include "Item.hpp"
#include "EntidadeBase.hpp"
#include "Repositories/RestauranteRepositorio.hpp"
#include "Repositories/ItemRepositorio.hpp"
#include "Repositories/DatabaseManager.hpp"

/**
    @class RestauranteServico
 * @brief Classe responsável pelo gerenciamento dos itens de um restaurante.
 */
class RestauranteServico
{
private:
    RestauranteRepositorio* _restauranteRepositorio;
    ItemRepositorio* _itemRepositorio;

    /**
     * @brief Editar um item do restaurante.
    */
    void EditarItemUnico(int id);

public:
    /**
     * @brief Construtor padrão.
     * @param dbManager Ponteiro para o gerenciador do banco de dados.
     */
    RestauranteServico(DatabaseManager* dbManager);

    /**
     * @brief Função em que o restaurante irá escolher a ação que deseja realizar.
     * @param restaurante Ponteiro para o objeto do restaurante.
     */
    void escolherAcao(Restaurante* restaurante);

    /**
     * @brief Exibe todos os itens do restaurante.
     * @param restaurante Ponteiro para o objeto do restaurante.
     */
    void exibirItens(Restaurante* restaurante);

    /**
     * @brief Adiciona um novo item ao restaurante.
     * @param restaurante Ponteiro para o objeto do restaurante.
     */
    void adicionarItem(Restaurante* restaurante);

    /**
     * @brief Remove um item do restaurante.
     * @param restaurante Ponteiro para o objeto do restaurante.
     */
    void removerItem(Restaurante* restaurante);

    /**
     * @brief Edita os itens do restaurante.
     * @param restaurante Ponteiro para o objeto do restaurante.
     */
    void editarItens(Restaurante* restaurante);
};

#endif // RESTAURANTE_SERVICO_HPP
