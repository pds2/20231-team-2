#include "Servicos/RemocaoServico.hpp"

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

RemocaoServico::RemocaoServico(DatabaseManager* dbManager)
{
    _clienteRepositorio = dbManager->GetClienteRepositorio();
    _restauranteRepositorio = dbManager->GetRestauranteRepositorio();
}

void RemocaoServico::DeletarRestaurante(Restaurante* restaurante)
{
    _restauranteRepositorio->Deletar(restaurante);
}

void RemocaoServico::DeletarCliente(Cliente* cliente)
{
    _clienteRepositorio->Deletar(cliente);
}

Usuario* RemocaoServico::RemoverUsuarioAtual(Usuario* usuario)
{
    TipoUsuario tipo = usuario->GetTipo();
    std::string descricaoTipo = (tipo == TipoUsuario::CLIENTE) ? "cliente" : "restaurante";

    std::cout << "\nOlá " << usuario->GetNome() << "." << std::endl;
    std::cout << "Informações do " << descricaoTipo << " atual: " << std::endl;
    std::cout << "Login: " << usuario->GetLogin() << std::endl; 
    std::cout << "Data de criação: " << usuario->GetDataDeCriacao() << std::endl; 
    std::string dataUltimaAtualizacao = usuario->GetDataUltimaAtualizacao();
    if (dataUltimaAtualizacao !=  "00:00 01/01/0001")
        std::cout << "Data da ultima atualização: " << dataUltimaAtualizacao << std::endl; 

    std::cout << std::endl;

    std::string escolha;
    std::cout << "Digite 'SIM' para " << VERMELHO << "confirmar a remoção." << RESET << " Outras entradas irão cancelar essa operação." << std::endl;
    std::cout << "Entrada: ";
    escolha = InputManager::LerString();

    if (escolha != "SIM")
    {
        std::cout << "\nOperação cancelada com" << VERDE << " sucesso!" << RESET << std::endl;
        return usuario;
    }
    
    if(tipo == TipoUsuario::CLIENTE)
    {
        Cliente* cliente = static_cast<Cliente*>(usuario);
        DeletarCliente(cliente);
    }
    else
    {
        Restaurante* restaurante = static_cast<Restaurante*>(usuario);
        DeletarRestaurante(restaurante);
    }

    std::cout << "\nO " << descricaoTipo << " foi removido com"  << VERDE << " sucesso!" << RESET << std::endl;
    return nullptr;
}