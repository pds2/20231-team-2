#include <iostream>
#include <functional>

#include "Cliente.hpp"
#include "Restaurante.hpp"
#include "Repositories/ClienteRepositorio.hpp"
#include "Repositories/RestauranteRepositorio.hpp"

#include "Servicos/AutenticacaoServico.hpp"

AutenticacaoServico::AutenticacaoServico(ClienteRepositorio* clienteRepositorio, RestauranteRepositorio* restauranteRepositorio)
{
    _clienteRepositorio = clienteRepositorio;
    _restauranteRepositorio = restauranteRepositorio;
}

void ImprimirMensagemInicial()
{
    std::cout << "+------------------------+" << std::endl;
    std::cout << "| MÓDULO DE AUTENTICAÇÃO |" << std::endl;
    std::cout << "+------------------------+\n" << std::endl;
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
    {
        return _restauranteRepositorio->BuscaPorLogin(login);
    }
    else if (std::is_same<Tipo, Restaurante>::value)
    {
        return _clienteRepositorio->BuscaPorLogin(login);
    }

    return nullptr;
}

template<typename Tipo>
Tipo* AutenticacaoServico::LoginGenerico(std::string mensagem_sucesso)
{
    static_assert(std::is_base_of<Usuario, Tipo>::value, "Tipo deve herdar de Usuario");

    ImprimirMensagemInicial();

    bool encerrar_login = false;
    while (!encerrar_login)
    {
        std::string login;

        std::cout << "Digite seu login: ";
        std::cin >> login;

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
                std::cout << "Login efetuado com sucesso. " << mensagem_sucesso << std::endl;
                return usuario;
            }
            else
            {
                std::cout << "Falha na autenticação, tentativas excedidas!" << std::endl;
                return nullptr;
            }
        }
        catch(const login_nao_encontrado_e e)
        {
            std::cout << "O login " << login << " não foi encontrado!" << std::endl;
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
        std::cin >> senha;

        if (senha == usuario->GetSenha())
            return true;

        std::cout << "Senha incorreta. " << tentativas_restantes << " tentativas restantes. \n" << std::endl;
    
        tentativas_restantes--;
    }

    return false;
}