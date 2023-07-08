#include <iostream>

#include "cores.hpp"
#include "Repositories/DatabaseManager.hpp"
#include "Servicos/AutenticacaoServico.hpp"
#include "Servicos/CadastroServico.hpp"
#include "Servicos/PedidoServico.hpp"

/// @brief 
/// @return 
int main()
{
    // Gerenciamento de acesso ao banco de dados.
    DatabaseManager * dbManager = new DatabaseManager();
    
    // Serviços responsáveis pelas funcionalidades do software.
    AutenticacaoServico autenticacaoServico = AutenticacaoServico(dbManager);
    CadastroServico cadastroServico = CadastroServico(dbManager);
    PedidoServico pedidoServico = PedidoServico(dbManager);

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
            std::cout << "[3] Logout." << std::endl;

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
            case 4:
                if (usuario_logado != nullptr)
                {
                    usuario_logado = nullptr;
                    break;
                }
            default:
                std::cout << "Opção inválida! Tente novamente." << std::endl;
        }

        std::cout << std::endl;

        if (usuario_logado == nullptr)
            continue;
        
        // Exibição das funcionalidades especificas de cada tipo de usuário.
        TipoUsuario tipo = usuario_logado->GetTipo();
        if (tipo == TipoUsuario::CLIENTE)
        {
            Cliente* cliente = static_cast<Cliente*>(usuario_logado);

            int opcao = -1;
            while (opcao != 0) 
            {
                std::cout << VERMELHO << "Bem-vindo(a) ao Menu dos clientes! " << RESET << std::endl;
                std::cout << "Escolha uma das opções abaixo:" << std::endl;
                std::cout << "[0] Sair." << std::endl;
                std::cout << "[1] Editar carteira." << std::endl;
                std::cout << "[2] Fazer um pedido." << std::endl;
                std::cout << "Opção escolhida: ";
                std::cin >> opcao;

                switch (opcao) 
                {
                    case 0:
                        std::cout << "Retornando ao menu principal..." << std::endl;
                        break;
                    case 1:
                        // Merge da PR pendente
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

            int opcao = -1;
            while (opcao != 0) 
            {
                std::cout << VERMELHO << "Bem-vindo(a) ao Menu dos restaurantes! " << RESET << std::endl;
                std::cout << "Escolha uma das opções abaixo:" << std::endl;
                std::cout << "[0] Sair." << std::endl;
                std::cout << "[1] ." << std::endl;
                std::cout << "[2] ." << std::endl;
                std::cout << "Opção escolhida: ";
                std::cin >> opcao;

                switch (opcao) 
                {
                    case 0:
                        std::cout << "Retornando ao menu principal..." << std::endl;
                        break;
                    case 1:
                        break;
                    case 2:
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