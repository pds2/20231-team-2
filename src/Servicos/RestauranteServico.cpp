#include <string>
#include <iostream>

#include "Usuario.hpp"
#include "Restaurante.hpp"
#include "Item.hpp"
#include "EntidadeBase.hpp"
#include "Servicos/RestauranteServico.hpp"
#include "Repositories/RestauranteRepositorio.hpp"
#include "Repositories/DatabaseManager.hpp"
#include "Repositories/ItemRepositorio.hpp"
#include "../../third_party/cores.hpp"

RestauranteServico::RestauranteServico(DatabaseManager* dbManager)
{
    _restauranteRepositorio = dbManager->GetRestauranteRepositorio();
    _itemRepositorio = dbManager->GetItemRepositorio();
}

void RestauranteServico::escolherAcao(Restaurante* restaurante)
{
    int opcao;
    std::cout << CIANO << "Seja Bem-Vindo, " << restaurante->GetNome() << "! Pressione: " << RESET << std::endl;
    std::cout << "[1] Ver os itens do restaurante" << std::endl;
    std::cout << "[2] Adicionar um novo item" << std::endl;
    std::cout << "[3] Remover um item existente" << std::endl;
    std::cout << "Opção: ";
    std::cin >> opcao;

    switch (opcao)
    {
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
            break;
    }
}

void RestauranteServico::exibirItens(Restaurante* restaurante)
{
    std::vector<Item*> itens = restaurante->GetItens();

    std::cout << CIANO << "Itens do Restaurante:" << RESET << std::endl;
    for (Item* item : itens)
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

void RestauranteServico::adicionarItem(Restaurante* restaurante)
{
    std::string nome, descricao;
    int tipo;
    double precoBase;

    std::cout << "Nome do item: ";
    std::cin >> nome;

    std::cout << "Descrição do item: ";
    std::cin >> descricao;

    std::cout << "Tipo do item (1-Bebidas, 2-Bebidas Alcoólicas, 3-Fast Food, 4-Prato Feito, 5-Doces): ";
    std::cin >> tipo;

    std::cout << "Preço base do item: ";
    std::cin >> precoBase;

    Item* novoItem = new Item(nome, descricao, static_cast<ItemType>(tipo), precoBase, restaurante->GetId());
    restaurante->AdicionarItem(novoItem);
}


void RestauranteServico::removerItem(Restaurante* restaurante)
{
    int idItem;

    std::cout << "ID do item a ser removido: ";
    std::cin >> idItem;

    Item* item = _itemRepositorio->BuscaPorId(idItem);
    if (item != nullptr && item->GetIdRestaurante() == restaurante->GetId())
    {
        restaurante->RemoverItem(item);
        std::cout << "Item removido com sucesso!" << std::endl;
    }
    else
    {
        std::cout << "Item não encontrado ou não pertence ao restaurante." << std::endl;
    }
}
