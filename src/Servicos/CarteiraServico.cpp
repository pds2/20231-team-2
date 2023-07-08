#include <string>
#include <iostream>

#include "Usuario.hpp"
#include "Cliente.hpp"
#include "Carteira.hpp"
#include "EntidadeBase.hpp"
#include "Servicos/CarteiraServico.hpp"

#include "Repositories/ClienteRepositorio.hpp"
#include "Repositories/DatabaseManager.hpp"
#include "Repositories/CarteiraRepositorio.hpp"

#include "../../third_party/cores.hpp"

CarteiraServico::CarteiraServico(DatabaseManager *dbManager) {
    _clienteRepositorio = dbManager->GetClienteRepositorio();
    _carteiraRepositorio = dbManager->GetCarteiraRepositorio();
}

void CarteiraServico::escolherAcao(Cliente *cliente) {
    int opcao;
    std::cout << CIANO << "Seja Bem-Vindo à sua carteira, " << cliente->GetNome() << "! Pressione: " << RESET << std::endl;
    std::cout << "[1] Ver o seu saldo" << std::endl;
    std::cout << "[2] Adicionar saldo" << std::endl;
    std::cout << "Opção: " << std::endl;
    std::cin >> opcao;

    switch (opcao) {
        case 1:
            imprimeSaldo(cliente);
            break;
        case 2:
            adicionaSaldo(cliente);
            break;
        default:
            break;
    }
}

void CarteiraServico::imprimeSaldo(Cliente *cliente) {
    if (cliente != nullptr && cliente->GetCarteira() != nullptr) {
        std::cout << CIANO << "O saldo atual da sua carteira é: " << cliente->GetCarteira()->GetSaldo() << RESET << std::endl;
    }
}

void CarteiraServico::adicionaSaldo(Cliente *cliente) {
    Carteira* carteira = cliente->GetCarteira();
    if (cliente != nullptr && carteira != nullptr) {
        double valor;
        std::cout << CIANO << "O saldo atual da sua carteira é: " << RESET << VERDE << cliente->GetCarteira()->GetSaldo() << RESET << std::endl;
        std::cout << "Qual valor você deseja adicionar? (insira no formato 0.0)" << std::endl;
        std::cout << "Valor: " << VERDE << std::endl;
        std::cin >> valor;

        carteira->AdicionarSaldo(valor);
        _carteiraRepositorio->Atualizar(carteira);
        std::cout << CIANO << "Agora o atual saldo da sua carteira é: " << carteira->GetSaldo() << RESET << std::endl;
    }
}
