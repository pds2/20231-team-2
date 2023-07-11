#pragma once

#ifndef RESTAURANTE_SERVICO_HPP
#define RESTAURANTE_SERVICO_HPP

#include <string>
#include <iostream>

#include "Restaurante.hpp"
#include "Item.hpp"
#include "Cupom.hpp"
#include "CupomBasico.hpp"
#include "CupomCustomizado.hpp"
#include "Cliente.hpp"
#include "EntidadeBase.hpp"
#include "Repositories/RestauranteRepositorio.hpp"
#include "Repositories/ItemRepositorio.hpp"
#include "Repositories/DatabaseManager.hpp"
#include "Repositories/CupomRepositorio.hpp"
#include "Repositories/ClienteRepositorio.hpp"

/**
    @class RestauranteServico
 * @brief Classe responsável pelo gerenciamento dos itens de um restaurante.
 */
class RestauranteServico
{
private:
    RestauranteRepositorio* _restauranteRepositorio;
    ItemRepositorio* _itemRepositorio;
    CupomRepositorio* _cupomRepositorio;
    ClienteRepositorio* _clienteRepositorio;

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

    /**
     * @brief Adiciona um novo cupom que passará a estar disponível a todos os clientes.
     */
    void adicionarCupom();
};

#endif // RESTAURANTE_SERVICO_HPP
