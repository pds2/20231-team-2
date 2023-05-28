#include <vector>
#include <string>

#include "../include/Carrinho.hpp"

Carrinho::Carrinho(){
  _valorTotal = 0.0;
}

double Carrinho::get_valorTotal(){
  return _valorTotal;
}

    
void Carrinho::adicionarItem(std::string item){
  _compras.push_back(item);
  //terminar de implementar após a definição da classe item
}

void Carrinho::removerItem(){
  //implementar depois que a classe Item estiver criada.  
}