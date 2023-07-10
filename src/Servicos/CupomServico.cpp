#include <string>
#include <iostream>
#include <iterator>
#include "../../include/Servicos/CupomServico.hpp"
#include "Utils/InputManager.hpp"
#include "cores.hpp"

CupomServico::CupomServico(DatabaseManager* dbManager){
    _clienteRepositorio = dbManager->GetClienteRepositorio();
}

void CupomServico::escolherAcaoCliente(Cliente* cliente){

    int opcao = -1;
    while (opcao != 0)
    {
        std::cout << CIANO << "Seja bem-vindo à área de cupons, " << cliente->GetNome() << "! Pressione: " << RESET << std::endl;
        std::cout << "[0] Sair do menu" << std::endl;
        std::cout << "[1] Ver seus cupons" << std::endl;
        std::cout << "Opção escolhida: ";
        opcao = InputManager::LerInt();
        std::cout << std::endl;

        switch (opcao)
        {
        case 0:
            break;
        case 1:
            listarCupomDoCliente(cliente);
            break;
        default:
            std::cout << VERMELHO << "Opção inválida! Tente novamente." << RESET << std::endl;
            break;
        }
    }
}

void CupomServico::listarCupomDoCliente(Cliente* cliente){
    if(cliente != nullptr){

        std::cout << "Estes são os cupons disponíveis para você:" << std::endl;
        std::cout << std::endl;

        if(cliente->GetCupons().size() != 0){
            std::vector<Cupom*> vetor_cupons = cliente->GetCupons();
        
            for(auto it = vetor_cupons.begin(); it != vetor_cupons.end(); it++){
                std::cout << VERDE << (**it).GetEtiqueta() << RESET << std::endl;
                std::cout << (**it).Descricao() << std::endl;
                std::cout << std::endl;
            }
        }else{
            std::cout << "Não existem cupons de compra ativos." << std::endl;
        }
    }else{
        std::cout << "Cliente não encontrado." << std::endl;
    }
}