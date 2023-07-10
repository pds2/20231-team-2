#include "../third_party/doctest.h"
#include "../include/Restaurante.hpp"
#include "Item.hpp"

TEST_CASE("Teste GetCNPJ"){
    Restaurante restaurante("nome", "login", "senha", "84.649.274/0001-04");
    CHECK(restaurante.GetDocumento() == "84.649.274/0001-04");

    Restaurante restaurante2("nome", "login", "senha", "84649274000104");
    CHECK(restaurante2.GetDocumento() == "84.649.274/0001-04");
}

TEST_CASE("Teste AdicionarItens"){
    Restaurante restaurante("nome", "login", "senha", "11.331.309/0001-80");
    
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
    Restaurante restaurante("nome", "login", "senha", "11.331.309/0001-80");
    
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