#include "../third_party/doctest.h"
#include "Restaurante.hpp"
#include "Item.hpp"

TEST_CASE("Teste GetCNPJ"){
    Restaurante restaurante("nome", "login", "senha", "123456789");
    CHECK(restaurante.GetCNPJ() == "123456789");
}

TEST_CASE("Teste AdicionarItens"){
    Restaurante restaurante("nome", "login", "senha", "123456789");
    
    Item item1("Item 1", "Descrição 1", ItemType::DOCES, 10.0, 1);
    Item item2("Item 2", "Descrição 2", ItemType::BEBIDAS_ALCOLICAS, 35.0, 1);

    restaurante.AdicionarItem(&item1);
    restaurante.AdicionarItem(&item2);

    std::vector<Item*> itens = restaurante.GetItens();
    CHECK(itens.size() == 2);
    CHECK(itens[0]->GetNome() == "Item 1");
    CHECK(itens[1]->GetNome() == "Item 2");
    CHECK(itens[0]->GetPrecoAtual() == 10.0);
    CHECK(itens[1]->GetPrecoAtual() == 35.0);
}

TEST_CASE("Teste RemoverItens"){
    Restaurante restaurante("nome", "login", "senha", "123456789");
    
    Item item1("Item 1", "Descrição 1", ItemType::DOCES, 10.0, 1);
    Item item2("Item 2", "Descrição 2", ItemType::BEBIDAS_ALCOLICAS, 35.0, 1);

    restaurante.AdicionarItem(&item1);
    restaurante.AdicionarItem(&item2);

    restaurante.RemoverItem(&item1);
    std::vector<Item*> itens = restaurante.GetItens();
    CHECK(itens.size() == 1);
    CHECK(itens[0]->GetNome() == "Item 2");
    CHECK(itens[0]->GetPrecoAtual() == 35.0);
}