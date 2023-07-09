#ifndef INPUTMANAGER_SERVICO_HPP
#define INPUTMANAGER_SERVICO_HPP

#include <string>
#include <iostream>

/**
 * Classe responsável por tratar os erros den entrada do usuário.
*/
class InputManager
{
    public:

        /**
         * @brief Responsável por ler um inteiro do usuário.
         * @returns O inteiro válido informado pelo usuário.
        */
        static int LerInt();    

        /**
         * @brief Responsável por ler um double do usuário.
         * @returns O double válido informado pelo usuário.
        */
        static double LerDouble();    

        /**
         * @brief Responsável por ler um float do usuário.
         * @returns O float válido informado pelo usuário.
        */
        static float LerFloat();  

        /**
         * @brief Responsável por ler uma string do usuário.
         * @returns A string válida(não vazia) informado pelo usuário.
        */
        static std::string LerString();      
};

#endif