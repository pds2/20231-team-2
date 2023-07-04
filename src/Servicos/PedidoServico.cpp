#include <iostream>
#include <vector>
#include <string>

#include "../../include/Repositories/CarrinhoRepositorio.hpp"
#include "../../include/Repositories/DatabaseManager.hpp"
#include "../../include/Servicos/PedidoServico.hpp"
#include "../../include/Restaurante.hpp"
#include "../../include/Carrinho.hpp"
#include "../../include/Item.hpp"

PedidoServico::PedidoServico(DatabaseManager * dbManager){
  _itemRepositorio = dbManager->GetItemRepositorio();
  _carrinhoRepositorio = dbManager->GetCarrinhoRepositorio();
}

void ImprimeInformacoesIniciais(int &verMenu){
  std::cout << "Pressione:" << std::endl;
  std::cout << "[1] - Para ver nossos restaurantes" << std::endl; 
  std::cout << "[2] - Para visualizar um Restaurante e ver seus itens disponíveis" << std::endl;
  std::cout << "[3] - Para criar um carrinho de Compras" << std::endl ;
  std::cout << "[4] - Para sair do Menu" << std::endl;
  std::cin >> verMenu;
}

void ImprimeSolicitacaoDoIdDoRestaurante(int &id){
  std::cout << "Por favor, forneça o ID do restaurante." << std::endl;
  std::cin >> id;
}

void ImprimeInformacoesdoCarrinho(std::string &editarCarrinho){
  std::cout << "Pronto para as compras?!" << std::endl;  
  std::cout << "Agora que você tem um carrinho, o que deseja fazer com ele?" << std::endl;
  std::cout << "Pressione:" << std::endl; 
  std::cout << "[e] - Para Adicionar ou Remover itens no seu carrinho de Compras" << std::endl;
  std::cout << "[f] - Para finalizar seu Pedido" << std::endl; 
  std::cout << "[s] - Para sair do Carrinho" << std::endl;
  std::cin >> editarCarrinho;
}

void ImprimeInstrucoesParaEdicaoDoCarrinho(int &id, std::string &edicao){
  std::cout << "Qual é o id item a ser adicionado/removido?" << std::endl;
  std::cin >> id;
  std::cout << "Para adicionar um item digite [a] e para remover digite [r]" << std::endl;
  std::cin >> edicao;
}

//TERMINAR DE IMPLEMENTAR(Sem utilidade ainda)
void ImprimeInformacoesParaEdicaoDoCarrinho(){
  std::cout << "Você deseja adicionar algum cupom ao seu carrinho? Digite [s] para ou [n] para não." << std::endl;
  //Preciso receber uma referência para cupom
  // std::cin >> cupom;
}

void ImprimeListaDeItensNoCarrinho(Carrinho *carrinho){
  std::cout << "Sua lista de compras é:" << std::endl;
  for(auto it : carrinho->GetCarrinho()){
    std::cout << it->GetNome() << " Preço: R$ " << it->GetPrecoAtual() << std::endl; 
  }
  std::cout << std::endl;
  std::cout << "O valor total do seu pedido é: R$ " << carrinho->GetValorTotal() << std::endl;
}


void PedidoServico::ImprimeMenu(Usuario *usuario){
  int verMenu;
  std::cout << "Bem-vindo " << usuario->GetNome() << "!" << std::endl; 
  do{
    ImprimeInformacoesIniciais(verMenu);
    switch (verMenu){
    case 1:
      ListarRestaurantes();
      break;
    case 2:{
      int id;
      ImprimeSolicitacaoDoIdDoRestaurante(id);
      ListarItensDeUmRestaurante(id);
      break;
    }
    case 3:{
      Carrinho *carrinho = new Carrinho(usuario->GetId());          
      std::string editarCarrinho;
      ImprimeInformacoesdoCarrinho(editarCarrinho);
      if (editarCarrinho == "e"){
        int id;
        std::string edicao;
        ImprimeInstrucoesParaEdicaoDoCarrinho(id, edicao);
        EditarCarrinho(carrinho, id, edicao);
      }else if (editarCarrinho == "f"){
        carrinho->Encerrar();
        ImprimeListaDeItensNoCarrinho(carrinho);
        _carrinhoRepositorio->Inserir(carrinho);
        delete carrinho;
      }else if (editarCarrinho != "s")
        std::cout << "Opção Inválida. Digite novamente" << std::endl;
      break;
    }
    default:
      std::cout << "Opção Inválida. Digite novamente" << std::endl;
      break;
    }
  } while (verMenu != 4);
}

void PedidoServico::ListarRestaurantes()
{
  std::cout << "Bem vindo ao (nome do Sistema): " << std::endl;
  std::cout << "Os restaurantes disponíveis são: " << std::endl;
  for (auto it : _Restaurantes)
  {
    std::cout << it.second->GetNome() << std::endl;
  }
}

void PedidoServico::ListarItensDeUmRestaurante(int id)
{
  for (auto it : _Restaurantes)
  {
    if (id == it.first)
    {
      Restaurante *restaurante = it.second;
      std::cout << "Bem vindo ao: " << restaurante->GetNome() << std::endl;
      std::cout << "Os nossos itens disponíveis para pedido são:" << std::endl;
      for (auto it : restaurante->GetItens())
      {
        std::cout << it->GetNome() << ": " << it->GetDescricao() << std::endl;
        std::cout << "Esse item está uma pechincha!! Ele custa apenas: " << it->GetPrecoAtual() << std::endl;
      }
    }
  }
}

void PedidoServico::EditarCarrinho(Carrinho *carrinho, int idDoItem, std::string AdicionarOuRemover){
  Item *item = _itemRepositorio->BuscaPorId(idDoItem);
  if(AdicionarOuRemover == "a"){
    carrinho->AdicionarItem(item);
  }

  if(AdicionarOuRemover == "r"){
    carrinho->RemoverItem(item);
  }
}

