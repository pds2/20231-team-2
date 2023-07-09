#include <string>
#include <iostream>

#include "Usuario.hpp"
#include "Restaurante.hpp"
#include "Item.hpp"
#include "EntidadeBase.hpp"
#include "Utils/InputManager.hpp"
#include "Servicos/RestauranteServico.hpp"
#include "Repositories/RestauranteRepositorio.hpp"
#include "Repositories/DatabaseManager.hpp"
#include "Repositories/ItemRepositorio.hpp"
#include "../../third_party/cores.hpp"

RestauranteServico::RestauranteServico(DatabaseManager *dbManager)
{
    _restauranteRepositorio = dbManager->GetRestauranteRepositorio();
    _itemRepositorio = dbManager->GetItemRepositorio();
}

void RestauranteServico::escolherAcao(Restaurante *restaurante)
{
    int opcao = -1;
    while (opcao != 0)
    {
        std::cout << CIANO << "Seja Bem-Vindo, " << restaurante->GetNome() << "! Pressione: " << RESET << std::endl;
        std::cout << "[0] Sair." << std::endl;
        std::cout << "[1] Ver os itens do restaurante." << std::endl;
        std::cout << "[2] Adicionar um novo item." << std::endl;
        std::cout << "[3] Remover um item existente." << std::endl;
        std::cout << "Opção: ";
        opcao = InputManager::LerInt();
        std::cout << std::endl;

        switch (opcao)
        {
        case 0:
            break;
        case 1:
            exibirItens(restaurante);
            break;
        case 2:
            adicionarItem(restaurante);
            break;
        case 3:
            removerItem(restaurante);
            break;
        default:
             std::cout << VERMELHO << "Opção inválida! Tente novamente." <<  RESET << std::endl;
        }
    }
}

void RestauranteServico::exibirItens(Restaurante *restaurante)
{
    std::vector<Item *> itens = restaurante->GetItens();

    std::cout << CIANO << "Itens do Restaurante:" << RESET << std::endl;
    for (Item *item : itens)
    {
        std::cout << "ID: " << item->GetId() << std::endl;
        std::cout << "Nome: " << item->GetNome() << std::endl;
        std::cout << "Descrição: " << item->GetDescricao() << std::endl;
        std::cout << "Tipo: " << static_cast<int>(item->GetTipo()) << std::endl;
        std::cout << "Preço Base: " << VERDE << item->GetPrecoBase() << RESET << std::endl;
        std::cout << "Preço Atual: " << VERDE << item->GetPrecoAtual() << RESET << std::endl;
        std::cout << std::endl;
    }
}

void RestauranteServico::adicionarItem(Restaurante *restaurante)
{
    std::string nome, descricao;
    int tipo;
    double precoBase;

    std::cout << "Nome do item: ";
    nome = InputManager::LerString();

    std::cout << "Descrição do item: ";
    descricao = InputManager::LerString();

    std::cout << "Tipo do item (1-Bebidas, 2-Bebidas Alcoólicas, 3-Fast Food, 4-Prato Feito, 5-Doces): ";
    tipo = InputManager::LerInt();

    std::cout << "Preço base do item: ";
    precoBase = InputManager::LerDouble();

    Item *novoItem = new Item(nome, descricao, static_cast<ItemType>(tipo), precoBase, restaurante->GetId());

    restaurante->AdicionarItem(novoItem);
    _restauranteRepositorio->AtualizarItens(restaurante);
}

void RestauranteServico::removerItem(Restaurante *restaurante)
{
    int idItem;

    std::cout << "ID do item a ser removido: ";
    idItem = InputManager::LerInt();

    Item *item = _itemRepositorio->BuscaPorId(idItem);
    if (item != nullptr && item->GetIdRestaurante() == restaurante->GetId())
    {
        restaurante->RemoverItem(item);
        _restauranteRepositorio->AtualizarItens(restaurante);

        std::cout << "Item removido com sucesso!" << std::endl;
    }
    else
    {
        std::cout << "Item não encontrado ou não pertence ao restaurante." << std::endl;
    }
}
