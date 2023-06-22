#include "../third_party/Sqlite/doctest/doctest.h"
#include "Carteira.hpp"
#include "Item.hpp"

TEST_CASE("Testando Carteira"){
  Carteira carteira = Carteira(10);

  SUBCASE("Adicionar e Remover Saldo"){
    carteira.AdicionarSaldo(10.0);
    CHECK(carteira.GetSaldo() == 10.0);

    carteira.AdicionarSaldo(5.0);
    CHECK(carteira.GetSaldo() == 15.0);

    CHECK_THROWS_AS(carteira.AdicionarSaldo(-5.0),impossivel_adicionar_saldo_negativo_ou_igual_a_zero_e);
    CHECK_THROWS_AS(carteira.AdicionarSaldo(0.0),impossivel_adicionar_saldo_negativo_ou_igual_a_zero_e);

    carteira.RemoverSaldo(5.0);
    CHECK(carteira.GetSaldo() == 10.0);

    carteira.RemoverSaldo(9.75);
    CHECK(carteira.GetSaldo() == 0.25);
    carteira.RemoverSaldo(0.25);
    CHECK(carteira.GetSaldo() == 0.0);

    CHECK(carteira.GetIdCliente() == 10);

    carteira.AdicionarSaldo(10.0);
    CHECK(carteira.GetSaldo() == 10.0);

    CHECK_THROWS_AS(carteira.RemoverSaldo(-5.0),impossivel_remover_saldo_negativo_ou_igual_a_zero_e);
    CHECK_THROWS_AS(carteira.RemoverSaldo(11.00), saldo_insuficiente_para_remocao_e);
    CHECK_THROWS_AS(carteira.RemoverSaldo(0.0), sem_saldo_e);
  }  
}