#include <iostream>
#include <sstream>
#include <cassert>

#include "doctest.h"
#include "Utils/InputManager.hpp"

/**
 * @brief Altera a saída padrão para que os std::cout não sejame exibidos no terminal.
 * @returns um ponteiro pra saída original do código.
*/
std::streambuf* AlterarSaidaPadrao()
{
    return std::cout.rdbuf(nullptr);
}

/**
 * @brief Retorna para a saída padrão.
 * @param original_cout ponteiro pra saída original.
*/
void RestaurarSaidaPadrao(std::streambuf* original_cout)
{
    std::cout.rdbuf(original_cout);
}

TEST_CASE("01 - Teste de leitura de inteiro.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("42\n");
    std::cin.rdbuf(input.rdbuf());

    int result = InputManager::LerInt();

    assert(result == 42);

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("02 - Teste de leitura inteiro com falha anterior.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("string\n42\n");
    std::cin.rdbuf(input.rdbuf());

    int result = InputManager::LerInt();

    assert(result == 42);

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("03 - Teste de leitura de float.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("3.14\n");
    std::cin.rdbuf(input.rdbuf());

    float result = InputManager::LerFloat();

    assert(result == 3.14f);

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("04 - Teste de leitura float com falha anterior.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("string\n3.14\n");
    std::cin.rdbuf(input.rdbuf());

    float result = InputManager::LerFloat();

    assert(result == 3.14f);

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("05 - Teste de leitura de double.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("2.71828\n");
    std::cin.rdbuf(input.rdbuf());

    double result = InputManager::LerDouble();

    assert(result == 2.71828);

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("06 - Teste de leitura double com falha anterior.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("string\n2.71828\n");
    std::cin.rdbuf(input.rdbuf());

    double result = InputManager::LerDouble();

    assert(result == 2.71828);

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("07 - Teste de leitura string simples.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("meutexto\n");
    std::cin.rdbuf(input.rdbuf());

    std::string result = InputManager::LerString();

    assert(result == "meutexto");

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("08 - Teste de leitura string simples com erro anterior.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("\nmeutexto\n");
    std::cin.rdbuf(input.rdbuf());

    std::string result = InputManager::LerString();

    assert(result == "meutexto");

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("09 - Teste de leitura string com espaços.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("meu texto\n");
    std::cin.rdbuf(input.rdbuf());

    std::string result = InputManager::LerString();

    assert(result == "meu texto");

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("10 - Teste de leitura string com espaços e erro anterior.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("\nmeu texto\n");
    std::cin.rdbuf(input.rdbuf());

    std::string result = InputManager::LerString();

    assert(result == "meu texto");

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("11 - Teste de leitura string com validação de espaços vazios.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("   \nmeu texto\n");
    std::cin.rdbuf(input.rdbuf());

    std::string result = InputManager::LerString();

    assert(result == "meu texto");

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("12 - Teste de leitura de inteiro com erro anterior com string com espaços.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("meu erro\n42\n");
    std::cin.rdbuf(input.rdbuf());

    int result = InputManager::LerInt();

    assert(result == 42);

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("13 - Teste de leitura de float com erro anterior com string com espaços.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("meu erro\n3.14\n");
    std::cin.rdbuf(input.rdbuf());

    float result = InputManager::LerFloat();

    assert(result == 3.14f);

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("14 - Teste de leitura de double com erro anterior com string com espaços.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("meu erro\n2.71828\n");
    std::cin.rdbuf(input.rdbuf());

    double result = InputManager::LerDouble();

    assert(result == 2.71828);

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("15 - Teste de leitura de CPF.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("12345678910\n");
    std::cin.rdbuf(input.rdbuf());

    std::string result = InputManager::LerDocumento(TipoUsuario::CLIENTE);

    assert(result == "12345678910");

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("16 - Teste de leitura de CPF com falhas anteriores.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("adadada\n \n12345678910\n");
    std::cin.rdbuf(input.rdbuf());

    std::string result = InputManager::LerDocumento(TipoUsuario::CLIENTE);

    assert(result == "12345678910");

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("17 - Teste de leitura de CPF com caracteres aleatórios que devem ser descartados.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("adasd123dasda456ada78910\n");
    std::cin.rdbuf(input.rdbuf());

    std::string result = InputManager::LerDocumento(TipoUsuario::CLIENTE);

    assert(result == "12345678910");

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("18 - Teste de leitura de CNPJ.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("21.241.369/0001-66\n");
    std::cin.rdbuf(input.rdbuf());

    std::string result = InputManager::LerDocumento(TipoUsuario::RESTAURANTE);

    assert(result == "21241369000166");

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("19 - Teste de leitura de CNPJ com falhas anteriores.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("adadada\n 21.241.369/0001-66\n");
    std::cin.rdbuf(input.rdbuf());

    std::string result = InputManager::LerDocumento(TipoUsuario::RESTAURANTE);

    assert(result == "21241369000166");

    RestaurarSaidaPadrao(original_cout);
}

TEST_CASE("20 - Teste de leitura de CNPJ com caracteres aleatórios que devem ser descartados.")
{
    std::streambuf* original_cout = AlterarSaidaPadrao();

    std::istringstream input("2as1.24adasdsd1.369/ada000adasda1-66\n");
    std::cin.rdbuf(input.rdbuf());

    std::string result = InputManager::LerDocumento(TipoUsuario::RESTAURANTE);

    assert(result == "21241369000166");

    RestaurarSaidaPadrao(original_cout);
}