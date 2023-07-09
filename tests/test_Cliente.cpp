#include "../third_party/doctest.h"
#include "../include/Cliente.hpp"

TEST_CASE("Teste GetCPF") {
    Cliente cliente("nome", "login", "senha", "123456789");
    CHECK(cliente.GetCPF() == "123456789");
}

TEST_CASE("Teste GetCarteira") {
    Cliente cliente("nome", "login", "senha", "123456789");
    Carteira* carteira = new Carteira(1);
    cliente.SetCarteira(carteira);
    CHECK(cliente.GetCarteira()->GetSaldo() == 0.0);
    delete carteira;
}

TEST_CASE("Teste AdicionarRemoverCarrinho") {
    Cliente cliente("Nome", "login", "senha", "123456789");
    Carrinho* carrinho1 = new Carrinho(1);
    Carrinho* carrinho2 = new Carrinho(1);
    cliente.AdicionarCarrinho(carrinho1);
    cliente.AdicionarCarrinho(carrinho2);

    std::vector<Carrinho*> carrinhos = cliente.GetCarrinhos();
    CHECK(carrinhos.size() == 2);

    cliente.RemoverCarrinho(carrinho1);
    carrinhos = cliente.GetCarrinhos();
    CHECK(carrinhos.size() == 1);

    delete carrinho1;
    delete carrinho2;
}

TEST_CASE("Testa adição e remoção de cupons"){
    Cliente cliente("Nome", "login", "senha", "123456789");
    Cupom* Dez = new Cupom("1", 5, 1);
    cliente.AdicionaCupom(Dez);

    CHECK(cliente.GetCupons().size() == 1);
}