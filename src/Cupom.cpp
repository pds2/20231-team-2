#include <string>

#include "../include/cupom.hpp"

Cupom::Cupom(std::string codigo, double desconto)
{
  _codigo = codigo;
  _desconto = desconto;
  _valido = true;
}
    
std::string Cupom::GetCodigo()
{
  return _codigo;
}

double Cupom::GetValor()
{
  return _desconto;
}

std::string Cupom::GetDataDeExpiracao()
{
  return _dataExpiracao;
}
      
    
bool Cupom::EstaValido(){
  //verificar se a data não é posterior a dataExpiração

  return _valido;
}
