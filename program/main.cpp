#include <iostream>

#include "Repositories/DatabaseManager.hpp"
#include "Servicos/AutenticacaoServico.hpp"

int main()
{
    DatabaseManager * dbManager = new DatabaseManager();
    AutenticacaoServico autenticacaoServico = AutenticacaoServico(dbManager);

    Usuario* usuario_logado = nullptr;

    int opcao;

    while (true) {
        std::cout << "Bem-vindo(a) ao Menu principal" << std::endl;
        std::cout << "Selecione uma opção:" << std::endl;
        std::cout << "1. Fazer login como cliente." << std::endl;
        std::cout << "2. Fazer login como restaurante." << std::endl;
        std::cout << "3. Sair" << std::endl;

        std::cout << "Opção escolhida: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                usuario_logado = autenticacaoServico.LoginCliente();
                break;
            case 2:
                usuario_logado = autenticacaoServico.LoginRestaurante();
                break;
            case 3:
                std::cout << "Saindo do programa..." << std::endl;
                return 0;
            default:
                std::cout << "Opção inválida! Tente novamente." << std::endl;
        }

        std::cout << std::endl;
    }
    
    delete dbManager;
    return 0;
}