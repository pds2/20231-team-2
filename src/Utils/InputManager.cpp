#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>

#include "cores.hpp"
#include "Utils/InputManager.hpp"

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

bool isStringEmptyOrWhitespace(const std::string& str) {
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
            
            if (isStringEmptyOrWhitespace(texto))
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