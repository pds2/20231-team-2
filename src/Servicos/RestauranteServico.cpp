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
    _cupomRepositorio = dbManager->GetCupomRepositorio();
    _clienteRepositorio = dbManager->GetClienteRepositorio();
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
        std::cout << "[5] Adicionar um cupom de desconto." << std::endl;
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
        case 5:
            adicionarCupom();
            break;
        default:
             std::cout << VERMELHO << "Opção inválida! Tente novamente." <<  RESET << std::endl;
        }
    }
}

std::string DescricaoTipoItem(ItemType tipo)
{
    switch (tipo)
    {
        case ItemType::BEBIDAS:
            return "Bebidas";

        case ItemType::BEBIDAS_ALCOLICAS:
            return "Bebidas Alcólicas";

        case ItemType::FAST_FOOD:
            return "Fast Food";

        case ItemType::PRATO_FEITO:
            return "Prato feito";
        
        case ItemType::DOCES:
            return "Doces";

        default:
            break;
    }

    return "Indefinido";
}

void ImprimirItem(Item* item)
{
    std::cout << "ID: " << item->GetId() << std::endl;
    std::cout << "Nome: " << item->GetNome() << std::endl;
    std::cout << "Descrição: " << item->GetDescricao() << std::endl;
    std::cout << "Tipo: " << DescricaoTipoItem(item->GetTipo()) << std::endl;
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
            alteracao = InputManager::LerInt();
            std::cout << std::endl;

            std::string nome, descricao;
            switch (alteracao)
            { 
                case 0:
                    std::cout << "Alteração do Id " << id << " encerrada." << std::endl;
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
    std::cout << "[0] Não." << std::endl;
    std::cout << "[1] Sim." << std::endl;
    std::cout << "Escolha: ";
    int listar_itens = InputManager::LerInt();
    std::cout << std::endl;

    if(listar_itens == 1)
        exibirItens(restaurante);

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

void RestauranteServico::adicionarCupom(){

    std::cout << std::endl;
    std::cout << "Qual tipo de cupom deseja criar?" << std::endl;
    std::cout << VERMELHO << "[0] CUPOM BÁSICO" << RESET << "  Basta apenas declarar um valor de desconto e uma etiqueta." << std::endl;
    std::cout << std::endl;
    std::cout << VERDE << "[1] CUPOM CUSTOMIZADO" << RESET << "  Crie um slogan customizado para o seu cupom, além do valor de desconto e etiqueta." << std::endl;
    std::cout << "Escolha: ";
    int escolha = InputManager::LerInt();

    while(escolha != 0 && escolha != 1){
        std::cout << "Opção inválida!" << std::endl;
        std::cout << std::endl;
        std::cout << "Qual tipo de cupom deseja criar?" << std::endl;
        std::cout << VERMELHO << "[0] CUPOM BÁSICO" << RESET << "  Basta apenas declarar um valor de desconto e uma etiqueta." << std::endl;
        std::cout << std::endl;
        std::cout << VERDE << "[1] CUPOM CUSTOMIZADO" << RESET << "  Crie um slogan customizado para o seu cupom, além do valor de desconto e etiqueta." << std::endl;
        std::cout << "Escolha: ";
        escolha = InputManager::LerInt();
    }

    //Lendo etiqueta
    std::cout << std::endl;
    std::cout << "Insira uma etiqueta para o cupom: (Ex: DIADASMAES15)" << std::endl;
    std::string etiqueta = InputManager::LerString();
    std::cout << std::endl;

    //Lendo valor do desconto
    std::cout << "Insira o valor do desconto em porcentagem. Por exemplo, caso queira dar um desconto de 10%, escreva '10', e não '0.1'. " << std::endl;
    double valor_desconto = InputManager::LerDouble();
    std::cout << std::endl;

    std::vector<Cliente*> clientes = _clienteRepositorio->ListarTodos();

    if(escolha == 0){

        //Criando cupom básico
        std::cout << "Confirma a criação do seguinte cupom?" << std::endl;
        std::cout << std::endl;
        std::cout << "ETIQUETA: " << etiqueta << std::endl;
        std::cout << "DESCONTO: " << valor_desconto << "%" << std::endl;
        std::cout << std::endl;
        std::cout << "[0] Não." << std::endl;
        std::cout << "[1] Sim." << std::endl;
        std::cout << "Escolha: ";
        escolha = InputManager::LerInt();
        std::cout << std::endl;

        while(escolha != 0 && escolha != 1){
            std::cout << "Opção inválida!" << std::endl;
            std::cout << std::endl;
            std::cout << "[0] Não." << std::endl;
            std::cout << "[1] Sim." << std::endl;
            std::cout << "Escolha: ";
            int escolha = InputManager::LerInt();
            std::cout << std::endl;
        }

        if(escolha == 1){
            
            for(auto cliente : clientes){
                Cupom* novo_cupom = new CupomBasico(etiqueta, valor_desconto, cliente->GetId());
                _cupomRepositorio->Inserir(novo_cupom);
            }
        }

    }else{
        
        //Criando cupom customizado

        //Lendo descrição customizada
        std::cout << "Insira uma descrição personalizada para o seu cupom." << std::endl;
        std::string descricao = InputManager::LerString();
        std::cout << std::endl;

        std::cout << "Confirma a criação do seguinte cupom?" << std::endl;
        std::cout << std::endl;
        std::cout << "ETIQUETA: " << etiqueta << std::endl;
        std::cout << "DESCONTO: " << valor_desconto << "%" << std::endl;
        std::cout << "DESCRIÇÃO: " << descricao << std::endl;
        std::cout << std::endl;
        std::cout << "[0] Não." << std::endl;
        std::cout << "[1] Sim." << std::endl;
        std::cout << "Escolha: ";
        escolha = InputManager::LerInt();
        std::cout << std::endl;

        while(escolha != 0 && escolha != 1){
            std::cout << "Opção inválida!" << std::endl;
            std::cout << std::endl;
            std::cout << "[0] Não." << std::endl;
            std::cout << "[1] Sim." << std::endl;
            std::cout << "Escolha: ";
            int escolha = InputManager::LerInt();
            std::cout << std::endl;
        }

        if(escolha == 1){
            
            for(auto cliente : clientes){
                Cupom* novo_cupom = new CupomCustomizado(etiqueta, valor_desconto, cliente->GetId(), descricao);
                _cupomRepositorio->Inserir(novo_cupom);
            }
        }
    }
}