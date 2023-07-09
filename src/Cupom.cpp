#include <string>

#include "Cupom.hpp"
#include "Cliente.hpp"

Cupom::Cupom(std::string codigo, double desconto, int idDoCliente)
{
  _codigo = codigo;
  _desconto = desconto;
  _valido = true;
  _idDoCliente = idDoCliente;
}
    
std::string Cupom::GetCodigo()
{
  return _codigo;
}

double Cupom::GetValor()
{
  return _desconto;
}  
    
bool Cupom::EstaValido(){
  return _valido;
}

void Cupom::SetaValido(){
  _valido = false;
}
