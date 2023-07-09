#include "doctest.h"

#include "Item.hpp"

TEST_CASE("Teste do construtor e dos métodos Get")
{
    Item item("Item 1", "Descrição do Item 1", ItemType::BEBIDAS, 10.0, 1);

    CHECK(item.GetNome() == "Item 1");
    CHECK(item.GetDescricao() == "Descrição do Item 1");
    CHECK(item.GetPrecoBase() == 10.0);
    CHECK(item.GetPrecoAtual() == 10.0);
    CHECK_FALSE(item.ExisteUmDescontoAplicado());

    item.AplicarDesconto(20);

    CHECK(item.GetPrecoAtual() == 8.0);
    CHECK(item.ExisteUmDescontoAplicado());

    item.RemoverDescontoAtual();

    CHECK(item.GetPrecoAtual() == 10.0);
    CHECK_FALSE(item.ExisteUmDescontoAplicado());
}

TEST_CASE("Teste dos métodos AplicarDesconto e RemoverDescontoAtual")
{
    Item item("Item 2", "Descrição do Item 2", ItemType::FAST_FOOD, 15.0, 2);

    CHECK(item.GetPrecoAtual() == 15.0);
    CHECK_FALSE(item.ExisteUmDescontoAplicado());

    item.AplicarDesconto(10);

    CHECK(item.GetPrecoAtual() == 13.5);
    CHECK(item.ExisteUmDescontoAplicado());

    item.AplicarDesconto(50);

    CHECK(item.GetPrecoAtual() == 7.5); //já que o desconto é aplicado no preço base.
    CHECK(item.ExisteUmDescontoAplicado());

    item.RemoverDescontoAtual();

    CHECK(item.GetPrecoAtual() == 15.0);
    CHECK_FALSE(item.ExisteUmDescontoAplicado());
}

TEST_CASE("Teste do método SetPrecoComDesconto")
{
    Item item("Item 3", "Descrição do Item 3", ItemType::DOCES, 8.0, 3);

    CHECK(item.GetPrecoAtual() == 8.0);
    CHECK_FALSE(item.ExisteUmDescontoAplicado());

    item.SetPrecoComDesconto(5.0);

    CHECK(item.GetPrecoAtual() == 5.0);
    CHECK(item.ExisteUmDescontoAplicado());

    item.SetPrecoComDesconto(8.0);

    CHECK(item.GetPrecoAtual() == 8.0);
    CHECK_FALSE(item.ExisteUmDescontoAplicado());
}

TEST_CASE("Teste de exceção do método AplicarDesconto")
{
    Item item("Item 4", "Descrição do Item 4", ItemType::BEBIDAS_ALCOLICAS, 20.0, 4);

    CHECK_THROWS(item.AplicarDesconto(-10));
    CHECK_THROWS(item.AplicarDesconto(0));
    CHECK_THROWS(item.AplicarDesconto(110));
}
