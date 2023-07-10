#include <regex>
#include <string>

#include "Utils/ValidadorDeDocumentos.hpp"

bool ValidadorDeDocumentos::ValidarCPF(std::string documento)
{
    std::string cpfLimpo = "";
    for (char c : documento) 
    {
        if (isdigit(c))
            cpfLimpo += c;
    }

    if (cpfLimpo.length() != 11)
        return false;

    if (!std::regex_match(cpfLimpo, std::regex("\\d+")))
        return false;

    return true;
}
        
bool ValidadorDeDocumentos::ValidarCNPJ(std::string documento)
{
    std::string cnpjLimpo = "";
    for (char c : documento) 
    {
        if (isdigit(c))
            cnpjLimpo += c;
    }

    if (cnpjLimpo.length() != 14)
        return false;

    if (!std::regex_match(cnpjLimpo, std::regex("\\d+"))) 
        return false;

    return true;
}