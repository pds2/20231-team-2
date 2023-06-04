#include <vector>
#include <string>
#include <iostream>

#include "../include/Carrinho.hpp"

Carrinho::Carrinho(){
  _valorTotal = 0.0;
}

double Carrinho::get_valorTotal(){
  return _valorTotal;
}


std::vector Carrinho::get_carrinho(){
  if(_compras.empty()){
    std::cout << "O carrinho esta vazio!" << std::endl;
  }
  return _compras;
}

    
void Carrinho::adicionarItem(Item &item){
  //Faltou lançar uma excessão para caso tente adicionar um item que não exista

  _compras.push_back(item);

  _valorTotal += item.GetPrecoAtual();
}

void Carrinho::removerItem(Item &item){
  //Faltou lançar uma excessão para caso tente remover um item que não exista.

  if(_compras.empty){
    throw carrinho_vazio_e();
  }

  /*Aqui eu considerei que o nome é o identificador único de um 
  item de determinado nome.Se for definido outro, como um codigo,
  irei mudar   */
  for(auto it: _compras){
    if(it.GetNome == item.GetNome()){
      _valorTotal -= item.GetPrecoAtual();
      _compras.erase(it);

      return;
    }
  }
  
  throw item_nao_existe_no_carrinho_e();
}

void Carrinho::limparCarrinho(){
  if(_compras.empty){
    throw carrinho_vazio_e();
  }

  _compras.clear();
}