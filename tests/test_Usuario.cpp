#include "../third_party/doctest.h"
#include "../include/Usuario.hpp"
#include "../include/Cliente.hpp"
#include "../include/Restaurante.hpp"

TEST_CASE("01 - Testando criação de Cliente e atribuição a Usuario*(já que usuário é uma classe abstrata)") {
    Cliente cliente("nome", "login", "12345", "68607597043");

    Usuario* usuario = &cliente;

    CHECK(usuario != nullptr);
    CHECK(usuario->GetNome() == "nome");
    CHECK(usuario->GetLogin() == "login");
    CHECK(usuario->GetSenha() == "12345");
    CHECK(usuario->GetTipo() == TipoUsuario::CLIENTE);
    CHECK(usuario->GetDocumento() == "686.075.970-43");
}

TEST_CASE("02 - Testando criação de Restaurante e atribuição a Usuario*(já que usuário é uma classe abstrata)") {
    Restaurante restaurante("nome", "login", "98765", "86541421000145");

    Usuario* usuario = &restaurante;

    CHECK(usuario != nullptr);
    CHECK(usuario->GetNome() == "nome");
    CHECK(usuario->GetLogin() == "login"); 
    CHECK(usuario->GetSenha() == "98765");
    CHECK(usuario->GetTipo() == TipoUsuario::RESTAURANTE);
    CHECK(usuario->GetDocumento() == "86.541.421/0001-45");
}

TEST_CASE("03 - Testando validação de documentos.")
{
    Cliente cliente("nome", "login", "12345", "68607597043");
    Usuario* usuarioCliente = &cliente;

    Restaurante restaurante("nome", "login", "98765", "86541421000145");
    Usuario* usuarioRestaurante = &restaurante;
    
    // Caracteres aleatórios
    CHECK_FALSE(usuarioCliente->DocumentoValido("dadadsdasad"));
    CHECK_FALSE(usuarioRestaurante->DocumentoValido("dadadsdasad"));

    // Corretos, usados na inicialização
    CHECK(usuarioCliente->DocumentoValido("68607597043"));
    CHECK(usuarioRestaurante->DocumentoValido("86541421000145"));

    // CPF e CNPJ invertidos
    CHECK_FALSE(usuarioCliente->DocumentoValido("86541421000145"));
    CHECK_FALSE(usuarioRestaurante->DocumentoValido("68607597043"));

    // Já formatados
    CHECK(usuarioCliente->DocumentoValido("686.075.970-43"));
    CHECK(usuarioRestaurante->DocumentoValido("86.541.421/0001-45"));

    // Já formatados invertendo CPF e CNPJ
    CHECK_FALSE(usuarioCliente->DocumentoValido("86.541.421/0001-45")); 
    CHECK_FALSE(usuarioRestaurante->DocumentoValido("686.075.970-43"));
}

TEST_CASE("04 - Testando lançamento de exceções quando o documento é inválido.")
{
    Cliente cliente("nome", "login", "12345", "68607597043");
    Usuario* usuarioCliente = &cliente;

    Restaurante restaurante("nome", "login", "98765", "86541421000145");
    Usuario* usuarioRestaurante = &restaurante;

    CHECK_THROWS(usuarioCliente->SetDocumento("adakjdakdbsd"));
    CHECK_THROWS(usuarioRestaurante->SetDocumento("adakjdakdbsd"));
}

TEST_CASE("05 - Testando atualização de documento correto.")
{
    Cliente cliente("nome", "login", "12345", "68607597043");
    Usuario* usuarioCliente = &cliente;

    Restaurante restaurante("nome", "login", "98765", "86541421000145");
    Usuario* usuarioRestaurante = &restaurante;

    usuarioCliente->SetDocumento("93210809020");
    CHECK(usuarioCliente->GetDocumento() == "932.108.090-20");

    usuarioRestaurante->SetDocumento("73284838000128");
    CHECK(usuarioRestaurante->GetDocumento() == "73.284.838/0001-28");
}

TEST_CASE("06 - Testando formatação de documentos.")
{
    Cliente cliente("nome", "login", "12345", "68607597043");
    Usuario* usuarioCliente = &cliente;

    Restaurante restaurante("nome", "login", "98765", "86541421000145");
    Usuario* usuarioRestaurante = &restaurante;

    std::string cpfFormatado = usuarioCliente->FormatarDocumento("93210809020");
    CHECK(cpfFormatado == "932.108.090-20");

    std::string cnpjFormatado = usuarioRestaurante->FormatarDocumento("73284838000128");
    CHECK(cnpjFormatado == "73.284.838/0001-28");
}