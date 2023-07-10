#ifndef VALIDADORDEDOCUMENTOS_HPP
#define VALIDADORDEDOCUMENTOS_HPP

#include <string>

/**
 * Classe responsável por validar documentos informados pelo usuário.
*/
class ValidadorDeDocumentos
{
    public:

        /**
         * @brief Responsável por checar um CPF.
         * @param documento cpf a ser validado.
         * @returns true se é válido.
        */
        static bool ValidarCPF(std::string documento);    

        /**
         * @brief Responsável por checar um CNPJ.
         * @param documento cnpj a ser validado.
         * @returns true se é válido.
        */
        static bool ValidarCNPJ(std::string documento);    
};

#endif