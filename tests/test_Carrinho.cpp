#include "../doctest/doctest.h"
#include "../include/Carrinho.hpp"
#include "../include/Item.hpp"

TEST_CASE("Testando Carrinho")
{
  Carrinho carrinho;
  Item item1 = Item("Agua Mineral", "Agua com Minerios", ItemType::BEBIDAS, 10.0, 1);
  Item item2 = Item("Hamburguer", "Pão, Hamburguer, Maionese", ItemType::FAST_FOOD, 20.0, 1);
  Item item3 = Item("Macarrao", "Massa e molho de tomate", ItemType::PRATO_FEITO, 15.0, 1);

  SUBCASE("Adicionar e remover itens")
  {
    carrinho.AdicionarItem(&item1);
    CHECK(carrinho.GetCarrinho().size() == 1);
    CHECK(carrinho.GetValorTotal() == 10.0);

    carrinho.AdicionarItem(&item2);
    CHECK(carrinho.GetCarrinho().size() == 2);
    CHECK(carrinho.GetValorTotal() == 30.0);

    carrinho.RemoverItem(&item1);
    CHECK(carrinho.GetCarrinho().size() == 1);
    CHECK(carrinho.GetValorTotal() == 20.0);
    CHECK(carrinho.GetCarrinho()[0]==&item2);

    carrinho.RemoverItem(&item2);
    CHECK(carrinho.GetCarrinho().size() == 0);
    CHECK(carrinho.GetValorTotal() == 0.0);
    CHECK(carrinho.GetCarrinho().empty());

    carrinho.AdicionarItem(&item1);    
    carrinho.AdicionarItem(&item2);
    carrinho.AdicionarItem(&item3);
    CHECK(carrinho.GetCarrinho().size() == 3);
    CHECK(carrinho.GetValorTotal() == 45.0);


    carrinho.RemoverItem(&item2);
    CHECK(carrinho.GetCarrinho()[1]==&item3);
    CHECK(carrinho.GetValorTotal() == 25.0);

    carrinho.LimparCarrinho();
    CHECK(carrinho.GetValorTotal() == 0.0);
    CHECK(carrinho.GetCarrinho().empty());

    CHECK_THROWS_AS(carrinho.RemoverItem(&item1), carrinho_vazio_e);

    carrinho.AdicionarItem(&item1);    
    carrinho.AdicionarItem(&item3);

    CHECK_THROWS_AS(carrinho.RemoverItem(&item2), item_nao_existe_no_carrinho_e);

    carrinho.LimparCarrinho();
    CHECK_THROWS_AS(carrinho.LimparCarrinho(), carrinho_vazio_e);
  }
}