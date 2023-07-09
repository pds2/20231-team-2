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
        std::cout << "[4] Editar itens atuais." << std::endl;
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
        case 4:
            editarItens(restaurante);
            break;
        default:
             std::cout << VERMELHO << "Opção inválida! Tente novamente." <<  RESET << std::endl;
        }
    }
}

void ImprimirItem(Item* item)
{
    std::cout << "ID: " << item->GetId() << std::endl;
    std::cout << "Nome: " << item->GetNome() << std::endl;
    std::cout << "Descrição: " << item->GetDescricao() << std::endl;
    std::cout << "Tipo: " << static_cast<int>(item->GetTipo()) << std::endl;
    std::cout << "Preço Base: " << VERDE << item->GetPrecoBase() << RESET << std::endl;
    std::cout << "Preço Atual: " << VERDE << item->GetPrecoAtual() << RESET << std::endl;
    std::cout << std::endl;
}

void RestauranteServico::exibirItens(Restaurante *restaurante)
{
    std::vector<Item *> itens = restaurante->GetItens();

    std::cout << CIANO << "Itens do Restaurante:" << RESET << std::endl;
    for (Item *item : itens)
    {
        ImprimirItem(item);
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
    std::cout << VERDE << "Item adicionado com sucesso!" << RESET << std::endl;
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

void RestauranteServico::EditarItemUnico(int id)
{
    try
    {
        Item* item = _itemRepositorio->BuscaPorId(id);
        std::cout << "Informações do item:" << std::endl;
        ImprimirItem(item);

        double preco, desconto;

        int alteracao = -1;        
        while(alteracao != 0)
        {
            std::cout << "Selecione o campo que deseja alterar:" << std::endl;
            std::cout << "[0] Sair." << std::endl;
            std::cout << "[1] Nome." << std::endl;
            std::cout << "[2] Descrição." << std::endl;
            std::cout << "[3] Preço." << std::endl;
            std::cout << "[4] Aplicar desconto." << std::endl;
            std::cout << "Escolha: ";
            int alteracao = InputManager::LerInt();
            std::cout << std::endl;

            std::string nome, descricao;
            switch (alteracao)
            { 
                case 0:
                    break;
                case 1:
                    std::cout << "Digite o novo nome: ";
                    nome = InputManager::LerString();
                    item->SetNome(nome);
                    break;
                case 2:
                    std::cout << "Digite a nova descrição: ";
                    descricao = InputManager::LerString();
                    item->SetDescricao(descricao);
                    break;
                case 3:
                    std::cout << "Digite o novo preço: ";
                    preco = InputManager::LerDouble();
                    item->SetPrecoBase(preco);
                    break;
                case 4:
                    std::cout << "Digite o desconto(porcentagem 1 a 100): ";
                    desconto = InputManager::LerDouble();
                    item->AplicarDesconto(desconto);
                    break;        
                default:
                    std::cout << VERMELHO << "Opção inválida! Tente novamente." <<  RESET << std::endl;
                    break;
            }
        }
    }
    catch(entidade_nao_encontrada_e e)
    {
        std::cout << "O item não foi encontrado." << std::endl;
    }
    catch(desconto_invalido_e e)
    {
        std::cout << "Desconto inválido." << std::endl;
    }
}

void RestauranteServico::editarItens(Restaurante* restaurante)
{
    std::cout << "Deseja listar os itens antes de editá-los?" << std::endl;
    std::cout << "[0] Sim." << std::endl;
    std::cout << "[1] Sim." << std::endl;
    int listar_itens = InputManager::LerInt();
    std::cout << std::endl;

    if(listar_itens == 1)
    {
        exibirItens(restaurante);
        std::cout << std::endl;
    }

    int escolha = -1;
    while(escolha != 0)
    {
        std::cout << "Selecione uma opção:" << std::endl;
        std::cout << "[0] Sair." << std::endl;
        std::cout << "[1] Sair " << VERMELHO << "sem salvar." << RESET << std::endl;
        std::cout << "[2] Editar um item." << std::endl;
        std::cout << "Escolha: ";
        escolha = InputManager::LerInt();
        std::cout << std::endl;

        int id;
        switch (escolha)
        {
            case 0:
                _restauranteRepositorio->AtualizarItens(restaurante);
                std::cout << VERDE << "Alterações salvas com sucesso!" <<  RESET << std::endl;
                break;
            case 1:
                std::cout << VERDE << "Alterações descartadas com sucesso!" <<  RESET << std::endl;
                break;
            case 2:
                std::cout << "Digite o id do item:";
                id = InputManager::LerInt();
                std::cout << std::endl;

                EditarItemUnico(id);
                break;
            default:
                std::cout << VERMELHO << "Opção inválida! Tente novamente." <<  RESET << std::endl;
        }
    }
}