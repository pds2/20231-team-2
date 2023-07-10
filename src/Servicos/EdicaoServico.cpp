#include "Servicos/EdicaoServico.hpp"

#include <string>
#include <iostream>

#include "cores.hpp"
#include "Usuario.hpp"
#include "Cliente.hpp"
#include "Restaurante.hpp"
#include "EntidadeBase.hpp"
#include "Utils/InputManager.hpp"
#include "Repositories/ClienteRepositorio.hpp"
#include "Repositories/DatabaseManager.hpp"
#include "Repositories/RestauranteRepositorio.hpp"

EdicaoServico::EdicaoServico(DatabaseManager* dbManager)
{
    _clienteRepositorio = dbManager->GetClienteRepositorio();
    _restauranteRepositorio = dbManager->GetRestauranteRepositorio();
}

bool EdicaoServico::LoginDisponivel(TipoUsuario tipo, std::string login, int ignorar)
{
    Usuario* usuario = nullptr;

    try
    {
      if (tipo == TipoUsuario::RESTAURANTE)
        usuario = _restauranteRepositorio->BuscaPorLogin(login);
      else if (tipo == TipoUsuario::CLIENTE)
        usuario =  _clienteRepositorio->BuscaPorLogin(login);
    }
    catch(entidade_nao_encontrada_e)
    {
      return true;
    }
    
    return usuario->GetId() == ignorar;
}

void EdicaoServico::AtualizarRestaurante(Restaurante* restaurante)
{
    _restauranteRepositorio->Atualizar(restaurante);
}

void EdicaoServico::AtualizarCliente(Cliente* cliente)
{
    _clienteRepositorio->Atualizar(cliente);
}

void ImprimeModuloEdicao()
{
    std::cout << "+------------------+" << std::endl;
    std::cout << "| " << CIANO << "MÓDULO DE EDIÇÃO" << RESET << " |" << std::endl;
    std::cout << "+------------------+\n" << std::endl;
}

void EdicaoServico::EditarUsuarioAtual(Usuario* usuario)
{
    ImprimeModuloEdicao();

    TipoUsuario tipo = usuario->GetTipo();
    std::string descricaoTipo = (tipo == TipoUsuario::CLIENTE) ? "cliente" : "restaurante";

    std::cout << "\nOlá " << usuario->GetNome() << "." << std::endl;
    std::cout << "Informações atuais do " << descricaoTipo << " atual: " << std::endl;
    std::cout << "Login: " << usuario->GetLogin() << std::endl; 
    std::cout << "Documento: " << usuario->GetDocumento() << std::endl;
    std::cout << "Data de criação: " << usuario->GetDataDeCriacao() << std::endl; 
    std::string dataUltimaAtualizacao = usuario->GetDataUltimaAtualizacao();
    if (dataUltimaAtualizacao !=  "00:00 01/01/0001")
        std::cout << "Data da ultima atualização: " << dataUltimaAtualizacao << std::endl; 

    std::cout << std::endl;

    std::cout << "Digite as " << VERDE << "novas" << RESET << " informações:" << std::endl;
    int escolha = -1;
    while(escolha != 0)
    {
        std::cout << "Selecione um campo para alterar:" << std::endl;
        std::cout << "[0] Sair." << std::endl;
        std::cout << "[1] Sair " << VERMELHO << "sem salvar." << RESET << std::endl;
        std::cout << "[2] Nome." << std::endl;
        std::cout << "[3] Login." << std::endl;
        std::cout << "[4] Senha." << std::endl;
        std::cout << "[5] Documento." << std::endl;
        std::cout << "Escolha: ";
        escolha = InputManager::LerInt();
        std::cout << std::endl;

        std::string nome, login, descricao, senha, documento;
        switch (escolha)
        {
            case 0:
                if(tipo == TipoUsuario::CLIENTE)
                {
                    Cliente* cliente = static_cast<Cliente*>(usuario);
                    AtualizarCliente(cliente);
                }
                else
                {
                    Restaurante* restaurante = static_cast<Restaurante*>(usuario);
                    AtualizarRestaurante(restaurante);
                }
                std::cout << VERDE << "Alterações salvas com sucesso!" <<  RESET << std::endl;
                return;
            case 1:
                std::cout << VERDE << "Alterações descartadas com sucesso!" <<  RESET << std::endl;
                return;
            case 2:
                std::cout << "Digite o novo nome: ";
                nome = InputManager::LerString();
                usuario->SetNome(nome);
                break;
            case 3:
                std::cout << "Digite o novo login: ";
                login = InputManager::LerString();

                if (!LoginDisponivel(usuario->GetTipo(), login, usuario->GetId()))
                {
                    std::cout << VERMELHO << "Login indisponível. Tente outro!" <<  RESET << std::endl;
                    break;
                }

                usuario->SetLogin(login);
                break;
            case 4:
                std::cout << "Digite a nova senha: ";
                senha = InputManager::LerString();
                usuario->SetSenha(senha);
                break;
            case 5:
                std::cout << "Digite o novo documento: ";
                documento = InputManager::LerDocumento(usuario->GetTipo());
                usuario->SetDocumento(documento);
                break;
            default:
                std::cout << VERMELHO << "Opção inválida! Tente novamente." <<  RESET << std::endl;
        }
    }  
}