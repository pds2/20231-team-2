#include <vector>
#include <string>
#include <iostream>

#include "Carrinho.hpp"
#include "EntidadeBase.hpp"
#include "Cupom.hpp"

Carrinho::Carrinho(int idCliente)
{
  _idCliente = idCliente;
  _pedidoEncerrado = false;
  _valorTotal = 0.0;
  _descontoAplicado = false;
}

double Carrinho::GetValorTotal(){
  return _valorTotal;
}

void Carrinho::AplicarDesconto(Cupom *cupom){
  if(_descontoAplicado == false){
     _valorTotal = _valorTotal * (100-cupom->GetValor())/100;
    SetValorTotal(_valorTotal);
    cupom->SetaValido();
    _descontoAplicado = true;
  }else{
    throw um_cupom_ja_foi_usado_e();
 }
}

void Carrinho::SetValorTotal(double valorTotal)
{
  _valorTotal = valorTotal;
}

std::vector<Item*> Carrinho::GetCarrinho(){
  if(_compras.empty()){
    return _compras;
  }
  return _compras;
}
    
void Carrinho::AdicionarItem(Item *item){
  _compras.push_back(item);

  _valorTotal += item->GetPrecoAtual();
}

void Carrinho::RemoverItem(Item *item){
  if(_compras.empty()){
    throw carrinho_vazio_e();
  }

  for(auto it=_compras.begin(); it != _compras.end(); it ++){
    if((*it)->GetId() == item->GetId()){
      _valorTotal -= item->GetPrecoAtual();
      _compras.erase(it);
      return;
    }
  }
  
  throw item_nao_existe_no_carrinho_e();
}

void Carrinho::LimparCarrinho(){
  if(_compras.empty()){
    throw carrinho_vazio_e();
  }
  
  _valorTotal = 0.0;
  _compras.clear();
}

void Carrinho::Encerrar()
{
  _pedidoEncerrado = true;
}

bool Carrinho::EstaEncerrado()
{
  return _pedidoEncerrado;
}

int Carrinho::GetIdCliente()
{
  return _idCliente;
}

void Carrinho::SetItens(std::vector<Item*> itens)
{
  _compras = itens;
}

void Carrinho::SetStatus(bool status)
{
  _pedidoEncerrado = status;
}

bool Carrinho::GetDescontoAplicado(){
  return _descontoAplicado;
}

