#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>

#include "cores.hpp"
#include "Usuario.hpp"
#include "Utils/InputManager.hpp"
#include "Utils/ValidadorDeDocumentos.hpp"

void ImprimeFalhaNumeros(std::string flag)
{
    std::cout << "O input está em um " << VERMELHO << "formato inválido" << RESET << "." << std::endl;
    std::cout << "Informe novamente um " << VERDE << flag << RESET << "." << std::endl;
    std::cout << "Nova entrada: ";
}

int InputManager::LerInt()
{   
    int inteiro;
    
    bool leitura_com_sucesso = false;
    while(!leitura_com_sucesso)
    {
        try
        {
            std::string input;
            std::getline(std::cin, input);

            size_t pos;
            inteiro = std::stoi(input, &pos);

            if (pos != input.size())
                throw std::invalid_argument("Formato inválido.");

            if (inteiro < std::numeric_limits<int>::min() || inteiro > std::numeric_limits<int>::max())
                throw std::out_of_range("Fora dos limites do tipo int.");

            leitura_com_sucesso = true;

        }
        catch(const std::exception& e)
        {
            ImprimeFalhaNumeros("inteiro");
        }
    }

    return inteiro;
}

float InputManager::LerFloat()
{   
    float decimal;

    bool leitura_com_sucesso = false;
    while (!leitura_com_sucesso)
    {
        try
        {
            std::string input;
            std::getline(std::cin, input);

            size_t pos;
            decimal = std::stof(input, &pos);

            if (pos != input.size())
                throw std::invalid_argument("Formato inválido.");

            if (decimal < std::numeric_limits<float>::lowest() || decimal > std::numeric_limits<float>::max())
                throw std::out_of_range("Fora dos limites do tipo float.");

            leitura_com_sucesso = true;
        }
        catch(const std::exception& e)
        {
            ImprimeFalhaNumeros("float");
        }
    }

    return decimal;
}

double InputManager::LerDouble()
{   
    double decimal;

    bool leitura_com_sucesso = false;
    while (!leitura_com_sucesso)
    {
        try
        {
            std::string input;
            std::getline(std::cin, input);

            size_t pos;
            decimal = std::stod(input, &pos);

            if (pos != input.size())
                throw std::invalid_argument("Formato inválido.");

            if (decimal < std::numeric_limits<double>::lowest() || decimal > std::numeric_limits<double>::max())
                throw std::out_of_range("Fora dos limites do tipo double.");

            leitura_com_sucesso = true;
        }
        catch(const std::exception& e)
        {
            ImprimeFalhaNumeros("double");
        }
    }

    return decimal;
}

void ImprimeFalhaString()
{
    std::cout << "\nA string informada é " << VERMELHO << "vazia" << RESET << "." << std::endl;
    std::cout << "Informe novamente uma " << VERDE << "string" << RESET << "." << std::endl;
    std::cout << "Nova entrada: ";
}

bool StringVazia(const std::string& str) {
    for (char c : str) {
        if (!std::isspace(c)) {
            return false;
        }
    }
    return true;
}

std::string InputManager::LerString()
{   
    std::string texto;

    bool leitura_com_sucesso = false;
    while(!leitura_com_sucesso)
    {
        try
        {
            std::getline(std::cin, texto);
            
            if (StringVazia(texto))
                throw std::exception();
            
            leitura_com_sucesso = true;
        }
        catch(const std::exception& e)
        {
            ImprimeFalhaString();
        }
    }

    return texto;
}

void ImprimeFalhaDocumento(std::string flag)
{
    std::cout << "\nA string informada é " << VERMELHO << "inválida" << RESET << "." << std::endl;
    std::cout << "Informe novamente uma " << VERDE << flag << RESET << "." << std::endl;
    std::cout << "Nova entrada: ";
}

std::string InputManager::LerDocumento(TipoUsuario tipo)
{
    std::string flag = (tipo == TipoUsuario::CLIENTE) ? "CPF" : "CNPJ";
    std::string documento;

    bool leitura_com_sucesso = false;
    while(!leitura_com_sucesso)
    {
        documento = LerString();

        if (tipo == TipoUsuario::CLIENTE)
            leitura_com_sucesso = ValidadorDeDocumentos::ValidarCNPJ(documento);
        else
            leitura_com_sucesso = ValidadorDeDocumentos::ValidarCNPJ(documento);

        if (!leitura_com_sucesso)
            ImprimeFalhaDocumento(flag);
    }

    return documento;
}