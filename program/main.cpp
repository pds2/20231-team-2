#include <iostream>

// Inclusão de cores pras saídas.
#include "cores.hpp"

// Inclusão do gerenciador de repositórios.
#include "Repositories/DatabaseManager.hpp"

// Inclusão dos serviços.
#include "Servicos/PedidoServico.hpp"
#include "Servicos/RemocaoServico.hpp"
#include "Servicos/CadastroServico.hpp"
#include "Servicos/CarteiraServico.hpp"
#include "Servicos/AutenticacaoServico.hpp"
#include "Servicos/RestauranteServico.hpp"

int main()
{
    // Gerenciamento de acesso ao banco de dados.
    DatabaseManager * dbManager = new DatabaseManager();
    
    // Serviços responsáveis pelas funcionalidades do software.
    AutenticacaoServico autenticacaoServico = AutenticacaoServico(dbManager);
    CadastroServico cadastroServico = CadastroServico(dbManager);
    RemocaoServico remocaoServico = RemocaoServico(dbManager);
    PedidoServico pedidoServico = PedidoServico(dbManager);
    CarteiraServico carteiraServico = CarteiraServico(dbManager);
    RestauranteServico restauranteServico = RestauranteServico(dbManager);

    // Usuário atual.
    Usuario* usuario_logado = nullptr;

    // Interações com o menu principal.
    int opcao = -1;
    while (opcao != 0) 
    {
        std::cout << VERMELHO << "Bem-vindo(a) ao Menu principal! " << RESET << std::endl;
        std::cout << "Escolha uma das opções abaixo:" << std::endl;
        std::cout << "[0] Sair." << std::endl;
        std::cout << "[1] Primeiro acesso." << std::endl;
        std::cout << "[2] Login." << std::endl;
        if (usuario_logado != nullptr)
        {
            std::cout << "[3] Logout." << std::endl;
            std::cout << "[4] " << VERMELHO << "Deletar" << RESET << " o usuário atual." << std::endl;
        }
            
        std::cout << "Opção escolhida: ";
        std::cin >> opcao;

        switch (opcao) 
        {
            case 0:
                std::cout << "Encerrando..." << std::endl;
                break;
            case 1:
                usuario_logado = cadastroServico.MenuCadastro();
                break;
            case 2:
                usuario_logado = autenticacaoServico.MenuLogin();
                break;
            case 3:
                if (usuario_logado != nullptr)
                {
                    usuario_logado = nullptr;
                    break;
                }
            case 4:
                if (usuario_logado != nullptr)
                {
                    usuario_logado = remocaoServico.RemoverUsuarioAtual(usuario_logado);
                    break;
                }
            default:
                std::cout << "Opção inválida! Tente novamente." << std::endl;
        }

        std::cout << std::endl;

        if (opcao == 0)
            break;

        if (usuario_logado == nullptr)
            continue;
        
        // Exibição das funcionalidades especificas de cada tipo de usuário.
        TipoUsuario tipo = usuario_logado->GetTipo();
        if (tipo == TipoUsuario::CLIENTE)
        {
            Cliente* cliente = static_cast<Cliente*>(usuario_logado);

            int opcao_cliente = -1;
            while (opcao_cliente != 0) 
            {
                std::cout << VERMELHO << "Bem-vindo(a) ao Menu dos clientes! " << RESET << std::endl;
                std::cout << "Escolha uma das opções abaixo:" << std::endl;
                std::cout << "[0] Sair." << std::endl;
                std::cout << "[1] Acessar a carteira." << std::endl;
                std::cout << "[2] Fazer um pedido." << std::endl;
                std::cout << "Opção escolhida: ";
                std::cin >> opcao_cliente;

                switch (opcao_cliente) 
                {
                    case 0:
                        std::cout << "Retornando ao menu principal..." << std::endl;
                        break;
                    case 1:
                        carteiraServico.escolherAcao(cliente);
                        break;
                    case 2:
                        pedidoServico.ImprimeMenu(cliente);
                        break;                            
                    default:
                        std::cout << "Opção inválida! Tente novamente." << std::endl;
                }
            }
        }
        else
        {
            Restaurante* restaurante = static_cast<Restaurante*>(usuario_logado);

            int opcao_restaurante = -1;
            while (opcao_restaurante != 0) 
            {
                std::cout << VERMELHO << "Bem-vindo(a) ao Menu dos restaurantes! " << RESET << std::endl;
                std::cout << "Escolha uma das opções abaixo:" << std::endl;
                std::cout << "[0] Sair." << std::endl;
                std::cout << "[1] Acessar central de controle." << std::endl;
                std::cout << "Opção escolhida: ";
                std::cin >> opcao_restaurante;

                switch (opcao_restaurante) 
                {
                    case 0:
                        std::cout << "Retornando ao menu principal..." << std::endl;
                        break;
                    case 1:
                        restauranteServico.escolherAcao(restaurante);
                        break;                          
                    default:
                        std::cout << "Opção inválida! Tente novamente." << std::endl;
                }
            }
        }

        std::cout << std::endl;
    }
    
    delete dbManager;
    return 0;
}