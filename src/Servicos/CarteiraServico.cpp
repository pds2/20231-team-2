#include <string>
#include <iostream>

#include "../../include/Usuario.hpp"
#include "../../include/Cliente.hpp"
#include "../../include/Carteira.hpp"
#include "../../include/EntidadeBase.hpp"
#include "../../include/Servicos/CarteiraServico.hpp"

#include "../../include/Repositories/ClienteRepositorio.hpp"
#include "../../include/Repositories/DatabaseManager.hpp"
#include "../../include/Repositories/CarteiraRepositorio.hpp"

#include "../../third_party/cores.hpp"

CarteiraServico::CarteiraServico(DatabaseManager *dbManager) {
    _clienteRepositorio = dbManager->GetClienteRepositorio();
    _carteiraRepositorio = dbManager->GetCarteiraRepositorio();
}

void CarteiraServico::escolherAcao(Usuario *usuario) {
    int opcao;
    std::cout << CIANO << "Seja Bem-Vindo à sua carteira, " << usuario->GetNome() << "! Pressione: " << RESET << std::endl;
    std::cout << "[1] Ver o seu saldo" << std::endl;
    std::cout << "[2] Adicionar saldo" << std::endl;
    std::cout << "Opção: ";
    std::cin >> opcao;

    switch (opcao) {
        case 1:
            imprimeSaldo(usuario);
            break;
        case 2:
            adicionaSaldo(usuario);
            break;
        default:
            break;
    }
}

void CarteiraServico::imprimeSaldo(Usuario *usuario) {
    Cliente *cliente = dynamic_cast<Cliente*>(usuario);
    if (cliente != nullptr && cliente->GetCarteira() != nullptr) {
        std::cout << CIANO << "O saldo da sua carteira é: " << cliente->GetCarteira()->GetSaldo() << RESET << std::endl;
    }
}

void CarteiraServico::adicionaSaldo(Usuario *usuario) {
    Cliente *cliente = dynamic_cast<Cliente*>(usuario);
    if (cliente != nullptr && cliente->GetCarteira() != nullptr) {
        double valor;
        std::cout << CIANO << "O saldo atual da sua carteira é: " << cliente->GetCarteira()->GetSaldo() << std::endl;
        std::cout << "Qual valor você deseja adicionar? (insira no formato 0.0)" << RESET << std::endl;
        std::cout << VERDE << "Valor: " << RESET << std::endl;
        std::cin >> valor;

        cliente->GetCarteira()->AdicionarSaldo(valor);
        std::cout << CIANO << "Agora o atual saldo da sua carteira é: " << cliente->GetCarteira()->GetSaldo() << RESET << std::endl;
    }
}
