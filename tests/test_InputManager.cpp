#include <iostream>
#include <sstream>
#include <cassert>

#include "doctest.h"
#include "Utils/InputManager.hpp"

TEST_CASE("01 - Teste de leitura de inteiro.")
{
    std::istringstream input("42\n");
    std::cin.rdbuf(input.rdbuf());

    int result = InputManager::LerInt();

    assert(result == 42);
}

TEST_CASE("02 - Teste de leitura inteiro com falha anterior.")
{
    std::istringstream input("string\n42\n");
    std::cin.rdbuf(input.rdbuf());

    int result = InputManager::LerInt();

    assert(result == 42);
}

TEST_CASE("03 - Teste de leitura de float.")
{
    std::istringstream input("3.14\n");
    std::cin.rdbuf(input.rdbuf());

    float result = InputManager::LerFloat();

    assert(result == 3.14f);
}

TEST_CASE("04 - Teste de leitura float com falha anterior.")
{
    std::istringstream input("string\n3.14\n");
    std::cin.rdbuf(input.rdbuf());

    float result = InputManager::LerFloat();

    assert(result == 3.14f);
}

TEST_CASE("05 - Teste de leitura de double.")
{
    std::istringstream input("2.71828\n");
    std::cin.rdbuf(input.rdbuf());

    double result = InputManager::LerDouble();

    assert(result == 2.71828);
}

TEST_CASE("06 - Teste de leitura double com falha anterior.")
{
    std::istringstream input("string\n2.71828\n");
    std::cin.rdbuf(input.rdbuf());

    double result = InputManager::LerDouble();

    assert(result == 2.71828);
}

TEST_CASE("07 - Teste de leitura string simples.")
{
    std::istringstream input("meutexto\n");
    std::cin.rdbuf(input.rdbuf());

    std::string result = InputManager::LerString();

    assert(result == "meutexto");
}

TEST_CASE("08 - Teste de leitura string simples com erro anterior.")
{
    std::istringstream input("\nmeutexto\n");
    std::cin.rdbuf(input.rdbuf());

    std::string result = InputManager::LerString();

    assert(result == "meutexto");
}

TEST_CASE("09 - Teste de leitura string com espaços.")
{
    std::istringstream input("meu texto\n");
    std::cin.rdbuf(input.rdbuf());

    std::string result = InputManager::LerString();

    assert(result == "meu texto");
}

TEST_CASE("10 - Teste de leitura string com espaços e erro anterior.")
{
    std::istringstream input("\nmeu texto\n");
    std::cin.rdbuf(input.rdbuf());

    std::string result = InputManager::LerString();

    assert(result == "meu texto");
}

TEST_CASE("11 - Teste de leitura string com validação de espaços vazios.")
{
    std::istringstream input("   \nmeu texto\n");
    std::cin.rdbuf(input.rdbuf());

    std::string result = InputManager::LerString();

    assert(result == "meu texto");
}

TEST_CASE("12 - Teste de leitura de inteiro com erro anterior com string com espaços.")
{
    std::istringstream input("meu erro\n42\n");
    std::cin.rdbuf(input.rdbuf());

    int result = InputManager::LerInt();

    assert(result == 42);
}

TEST_CASE("13 - Teste de leitura de float com erro anterior com string com espaços.")
{
    std::istringstream input("meu erro\n3.14\n");
    std::cin.rdbuf(input.rdbuf());

    float result = InputManager::LerFloat();

    assert(result == 3.14f);
}

TEST_CASE("14 - Teste de leitura de double com erro anterior com string com espaços.")
{
    std::istringstream input("meu erro\n2.71828\n");
    std::cin.rdbuf(input.rdbuf());

    double result = InputManager::LerDouble();

    assert(result == 2.71828);
}