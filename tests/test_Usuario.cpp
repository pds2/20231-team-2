#include "../third_party/doctest.h"
#include "../include/Usuario.hpp"
#include "../include/Cliente.hpp"
#include "../include/Restaurante.hpp"

TEST_CASE("02 - Testando criação de Cliente e atribuição a Usuario*(já que usuário é uma classe abstrata)") {
    Cliente cliente("nome", "login", "12345", "1234567890");

    Usuario* usuario = &cliente;

    CHECK(usuario != nullptr);
    CHECK(usuario->GetNome() == "nome");
    CHECK(usuario->GetLogin() == "login");
    CHECK(usuario->GetSenha() == "12345");
    CHECK(usuario->GetTipo() == TipoUsuario::CLIENTE);
}

TEST_CASE("03 - Testando criação de Restaurante e atribuição a Usuario*(já que usuário é uma classe abstrata)") {
    Restaurante restaurante("nome", "login", "98765", "12345678901234");

    Usuario* usuario = &restaurante;

    CHECK(usuario != nullptr);
    CHECK(usuario->GetNome() == "nome");
    CHECK(usuario->GetLogin() == "login");
    CHECK(usuario->GetSenha() == "98765");
    CHECK(usuario->GetTipo() == TipoUsuario::RESTAURANTE);
}