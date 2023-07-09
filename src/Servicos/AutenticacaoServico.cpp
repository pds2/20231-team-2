#include <iostream>
#include <type_traits>

#include "cores.hpp"
#include "Cliente.hpp"
#include "Restaurante.hpp"
#include "Utils/InputManager.hpp"
#include "Repositories/DatabaseManager.hpp"
#include "Servicos/AutenticacaoServico.hpp"

AutenticacaoServico::AutenticacaoServico(DatabaseManager * dbManager)
{
    _clienteRepositorio = dbManager->GetClienteRepositorio();
    _restauranteRepositorio = dbManager->GetRestauranteRepositorio();
}

void ImprimeModulo()
{
    std::cout << "\n+------------------------+" << std::endl;
    std::cout << "| " << CIANO << "MÓDULO DE AUTENTICAÇÃO" << RESET << " |" << std::endl;
    std::cout << "+------------------------+\n" << std::endl;
}

Usuario* AutenticacaoServico::MenuLogin()
{
    ImprimeModulo();

    int escolha = -1;
    while (escolha != 0)
    {
        std::cout << "Selecione sua função: " << std::endl;
        std::cout << "[0] Cancelar." << std::endl;
        std::cout << "[1] Cliente. " << std::endl;
        std::cout << "[2] Restaurante." << std::endl;
        std::cout << "Opão escolhida: ";
        escolha = InputManager::LerInt();
        std::cout << std::endl;

        switch (escolha)
        {
            case 0:
                std::cout << "Retornando ao menu principal." << std::endl;
                break;
            case 1:
                return LoginCliente();
                break;
            case 2:
                return LoginRestaurante();
                break;
            default:
                std::cout << "Opção inválida! Tente novamente." << std::endl;
        }   
    }

    return nullptr;
}

Cliente* AutenticacaoServico::LoginCliente()
{
    std::string mensagem = "Boas compras!";
    return LoginGenerico<Cliente>(mensagem);
}

Restaurante* AutenticacaoServico::LoginRestaurante()
{
    std::string mensagem = "Bom trabalho!";
    return LoginGenerico<Restaurante>(mensagem);
}

template<typename Tipo>
Usuario* AutenticacaoServico::BuscaUsuario(std::string login)
{
    if (std::is_same<Tipo, Restaurante>::value)
        return _restauranteRepositorio->BuscaPorLogin(login);
    else if (std::is_same<Tipo, Cliente>::value)
        return _clienteRepositorio->BuscaPorLogin(login);

    return nullptr;
}

template<typename Tipo>
Tipo* AutenticacaoServico::LoginGenerico(std::string mensagem_sucesso)
{
    bool encerrar_login = false;
    while (!encerrar_login)
    {
        std::string login;

        std::cout << "Digite seu login: ";
        login = InputManager::LerString();

        if (login == "encerrar")
        {
            std::cout << "Autenticação cancelada com sucesso." << std::endl;
            return nullptr;
        }

        try
        {
            Tipo* usuario = static_cast<Tipo*>(BuscaUsuario<Tipo>(login));
    
            if (SenhaValida(usuario))
            {
                std::cout << VERDE << "Login efetuado com sucesso. " << mensagem_sucesso << RESET << std::endl;
                return usuario;
            }
            else
            {
                std::cout << VERMELHO << "Falha na autenticação, tentativas excedidas!" << RESET << std::endl;
                return nullptr;
            }
        }
        catch(const entidade_nao_encontrada_e e)
        {
            std::cout << VERMELHO << "O login '" << login << "' não foi encontrado!" << RESET << std::endl;
            std::cout << "Tente novamente ou digite 'encerrar' como login para retornar ao menu principal. \n" << std::endl;
        }
    }

    return nullptr;
}

bool AutenticacaoServico::SenhaValida(Usuario* usuario)
{
    int tentativas_restantes = 3;

    while(tentativas_restantes > 0)
    {
        std::string senha;

        std::cout << "Digite sua senha: ";
        senha = InputManager::LerString();

        if (senha == usuario->GetSenha())
            return true;

        tentativas_restantes--;
        std::cout << "Senha incorreta. " << tentativas_restantes << " tentativas restantes. \n" << std::endl;        
    }

    return false;
}

void AutenticacaoServico::EditarSenha(Usuario* usuario)
{
    ImprimeModulo();

    std::cout << "Digite a senha antiga: ";
    std::string antiga = InputManager::LerString();
    
    if (antiga != usuario->GetSenha())
    {
        std::cout << VERMELHO << "Senha incorreta. Alteração cancelada!" << RESET << std::endl;
        return;
    }

    std::cout << "Digite a nova senha: ";
    std::string nova = InputManager::LerString();
    usuario->SetSenha(nova);

    if (usuario->GetTipo() == TipoUsuario::CLIENTE)
    {
        Cliente* cliente = static_cast<Cliente*>(usuario);
        _clienteRepositorio->Atualizar(cliente);
    }
    else
    {
        Restaurante* restaurante = static_cast<Restaurante*>(usuario);
        _restauranteRepositorio->Atualizar(restaurante);
    }

    std::cout << "Senha atualizada com " << VERDE << "sucesso." << RESET << std::endl;
}