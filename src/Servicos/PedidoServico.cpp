#include <vector>
#include <string>
#include <iostream>

#include "Servicos/PedidoServico.hpp"
#include "Repositories/DatabaseManager.hpp"
#include "Repositories/CarteiraRepositorio.hpp"
#include "Repositories/CarrinhoRepositorio.hpp"
#include "Repositories/CupomRepositorio.hpp"

#include "Item.hpp"
#include "cores.hpp"
#include "Cliente.hpp"
#include "Carrinho.hpp"
#include "Restaurante.hpp"
#include "Utils/InputManager.hpp"

PedidoServico::PedidoServico(DatabaseManager *dbManager)
{
  _itemRepositorio = dbManager->GetItemRepositorio();
  _carrinhoRepositorio = dbManager->GetCarrinhoRepositorio();
  _carteiraRepositorio = dbManager->GetCarteiraRepositorio();
  _cupomRepositorio = dbManager->GetCupomRepositorio();
  _RestaurantesRepositorio = dbManager->GetRestauranteRepositorio();
}

void ImprimeInformacoesIniciais(int &verMenu)
{
  std::cout << CIANO << "Pressione:" << RESET << std::endl;
  std::cout << "[1]  Para ver nossos restaurantes" << std::endl;
  std::cout << "[2]  Para visualizar um Restaurante e ver seus itens disponíveis" << std::endl;
  std::cout << "[3]  Para criar/editar um carrinho de Compras" << std::endl;
  std::cout << "[4]  Para ver suas compras anteriores" << std::endl;
  std::cout << "[5]  Para sair do Menu" << std::endl;  
  std::cout << "Opção escolhida: ";
  verMenu = InputManager::LerInt();
  std::cout << std::endl;
}

void ImprimeSolicitacaoDoIdDoRestaurante(int &id)
{
  std::cout << "Por favor, forneça o ID do restaurante." << std::endl;
  id = InputManager::LerInt();
}

void ImprimeInformacoesdoCarrinho(std::string &editarCarrinho)
{
  std::cout << CIANO << "Pronto para as compras?!" << std::endl;
  std::cout << "Agora que você tem um carrinho, o que deseja fazer com ele?" << RESET << std::endl;
  std::cout << "Pressione:" << std::endl;
  std::cout << "[e]  Para Adicionar ou Remover itens no seu carrinho de Compras" << std::endl;
  std::cout << "[l]  Para Limpar seu carrinho" << std::endl;
  std::cout << "[f]  Para finalizar seu Pedido" << std::endl;
  std::cout << "[v]  Para visualizar o carrinho" << std::endl;
  std::cout << "[s]  Para sair do Carrinho" << std::endl;
  std::cout << "Opção escolhida: ";
  editarCarrinho = InputManager::LerString();
  std::cout << std::endl;
}

void ImprimeInstrucoesParaEdicaoDoCarrinho(int &id, std::string &edicao)
{
  std::cout << "Qual é o id item a ser adicionado/removido?" << std::endl;
  id = InputManager::LerInt();
  std::cout << "Para adicionar um item digite [a] e para remover digite [r]" << std::endl;
  edicao = InputManager::LerString();
}

void PedidoServico::AplicaCupom(std::string &aplicarCupom, Cliente *cliente, Carrinho *carrinho)
{
  std::cout << "Você deseja adicionar algum cupom ao seu carrinho? Digite [s] para sim ou [n] para não." << std::endl;
  aplicarCupom = InputManager::LerString();
  if (aplicarCupom == "s")
  {
    int id;
    std::cout << "Por favor, digite o id do Cupom." << std::endl;
    id = InputManager::LerInt();
    try
    {
      Cupom *cupom = cliente->GetCupom(id);
      carrinho->AplicarDesconto(cupom);
      cupom->SetaValido();
      _cupomRepositorio->Atualizar(cupom);
    }
    catch (um_cupom_ja_foi_usado_e)
    {
      std::cout << VERMELHO << "Voce ja usou um cupom." << RESET << std::endl;
    }
    catch(cupom_nao_existe_e){
      std::cout << VERMELHO << "Esse cupom não existe." << RESET << std::endl;
    }
  }
}

void ImprimeValorFinalDoCarrinho(Carrinho *carrinho){
  std::cout << AMARELO << "O valor total do seu pedido é: R$ " << carrinho->GetValorTotal() << RESET << std::endl;
  std::cout << std::endl;
}

void ImprimeListaDeItensNoCarrinho(Carrinho *carrinho)
{
  std::cout << "Sua lista de compras é:" << std::endl;
  for (auto it : carrinho->GetCarrinho())
  {
    std::cout << it->GetNome() << " - Preço: R$ " << it->GetPrecoAtual() << std::endl;
  }
}

void ImprimeComprasAnteriores(Cliente *cliente){
  for(Carrinho *carrinho: cliente->GetCarrinhos()){
    if(carrinho->EstaEncerrado()){
      ImprimeListaDeItensNoCarrinho(carrinho);
    }     
    ImprimeValorFinalDoCarrinho(carrinho);
  }
}


void PedidoServico::ListarRestaurantes()
{
  std::cout << VERMELHO << "Bem vindo ao UfmgFood: " << std::endl;
  std::cout << "Os restaurantes disponíveis são: " << RESET << std::endl;

  for (auto it : _RestaurantesRepositorio->ListarTodos())
  {
    std::cout << it->GetNome() << ". O id do Restaurante é: " << it->GetId() << std::endl;
  }
}

void PedidoServico::ListarItensDeUmRestaurante(int id)
{
  try
  {
    Restaurante *restaurante = _RestaurantesRepositorio->BuscaPorId(id);
    std::cout << "Bem vindo ao: " << restaurante->GetNome() << std::endl;
    std::cout << "Os nossos itens disponíveis para pedido são: " << std::endl;
    for (auto it : restaurante->GetItens())
    {
      std::cout << it->GetNome() << ": " << it->GetDescricao() << std::endl;
      std::cout << "Esse item está uma pechincha!! Ele custa apenas: " << it->GetPrecoAtual() << ". O id do item é: " << it->GetId() << std::endl;
    }
  }
  catch (entidade_nao_encontrada_e)
  {
    std::cout << VERMELHO << "Nao existe Restaurante com esse id" << RESET << std::endl;
  }
}

void PedidoServico::EditarCarrinho(Carrinho *carrinho, int idDoItem, std::string AdicionarOuRemover)
{
  try
  {
    Item *item = _itemRepositorio->BuscaPorId(idDoItem);
    if (AdicionarOuRemover == "a")
    {
      carrinho->AdicionarItem(item);
    }
    if (AdicionarOuRemover == "r")
    {
      try
      {
        carrinho->RemoverItem(item);
      }
      catch (carrinho_vazio_e)
      {
        std::cout << VERMELHO << "Seu carrinho está vazio." << RESET << std::endl;
      }
      catch (item_nao_existe_no_carrinho_e)
      {
        std::cout << VERMELHO << "Este item não está no seu Carrinho." << RESET << std::endl;
      }
    }
  }
  catch (entidade_nao_encontrada_e)
  {
    std::cout << VERMELHO << "Este item nao existe." << RESET << std::endl;
  }
}

void PedidoServico::LimparCarrinho(Carrinho *carrinho)
{
  try
  {
    carrinho->LimparCarrinho();
  }
  catch (item_nao_existe_no_carrinho_e &e)
  {
    std::cout << VERMELHO << "Carrinho já está vazio." << RESET << std::endl;
  }
}

void PedidoServico::EncerrarCarrinho(Carrinho *carrinho, Cliente *cliente)
{
  try
  {
    cliente->GetCarteira()->RemoverSaldo(carrinho->GetValorTotal());
    Carteira *carteira = cliente->GetCarteira();
    _carteiraRepositorio->Atualizar(carteira);
    carrinho->Encerrar();
    ImprimeListaDeItensNoCarrinho(carrinho);
  }
  catch (saldo_insuficiente_para_remocao_e &e)
  {
    std::cout << VERMELHO << "Saldo Insuficiente" << RESET << std::endl;
    std::cout << VERDE << "Por favor, feche o Menu, e adicione mais saldo para finalizar o pedido!" << RESET << std::endl;
  }catch(impossivel_remover_saldo_negativo_ou_igual_a_zero_e){
    std::cout << VERMELHO << "Seu carrinho está vazio" << RESET << std::endl;
  }
}

void PedidoServico::MenuDoCarrinho(Cliente *cliente){
  Carrinho *carrinho = new Carrinho(cliente->GetId());
  std::string editarCarrinho;
  do{
    ImprimeInformacoesdoCarrinho(editarCarrinho);
    if (editarCarrinho == "e")
    {
      int id;
      std::string edicao;
      ImprimeInstrucoesParaEdicaoDoCarrinho(id, edicao);
      EditarCarrinho(carrinho, id, edicao);
    }
    else if (editarCarrinho == "l")
    {
      LimparCarrinho(carrinho);
    }
    else if(editarCarrinho == "v"){
      ImprimeListaDeItensNoCarrinho(carrinho);
      ImprimeValorFinalDoCarrinho(carrinho);
    }
    else if (editarCarrinho == "f")
    {
      std::string aplicarCupom;
      AplicaCupom(aplicarCupom, cliente, carrinho);
      EncerrarCarrinho(carrinho, cliente);
      ImprimeValorFinalDoCarrinho(carrinho);
      _carrinhoRepositorio->Inserir(carrinho); 
      cliente->AdicionarCarrinho(carrinho);     
      break;
    }else if(editarCarrinho == "s"){
      break;
    }
      std::cout << "Opção Inválida. Digite novamente" << std::endl;
  }while(editarCarrinho != "s" || editarCarrinho !="f");
}

void PedidoServico::ImprimeMenu(Cliente *cliente)
{
  int verMenu;
  std::cout << "Bem-vindo(a) " << cliente->GetNome() << "!" << std::endl;
  do
  {
    ImprimeInformacoesIniciais(verMenu);
    switch (verMenu)
    {
      case 1:
        ListarRestaurantes();
        break;
      case 2:
      {
        int id;
        ImprimeSolicitacaoDoIdDoRestaurante(id);
        ListarItensDeUmRestaurante(id);
        break;
      }
      case 3:
      {
        MenuDoCarrinho(cliente);
        break;
      }
      case 4:
        ImprimeComprasAnteriores(cliente);
        break;
      case 5:
        break;
      default:
        std::cout << VERMELHO << "Opção Inválida. Digite novamente" << RESET << std::endl;
        break;
      }
  } while (verMenu != 4);
}
