#include <string>

#include "../include/cupom.hpp"

Cupom::Cupom(std::string codigo, double desconto)
{
  _codigo = codigo;
  _desconto = desconto;
  _valido = true;
}
    
std::string Cupom::get_codigo()
{
  return _codigo;
}

double Cupom::get_valor()
{
  return _desconto;
}

std::string Cupom::get_dataExpiracao()
{
  return _dataExpiracao;
}
      
    
bool Cupom::estaValido(){
  //verificar se a data não é posterior a dataExpiração

  return _valido;
}
