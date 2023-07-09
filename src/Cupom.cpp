#include <string>

#include "Cupom.hpp"

int Cupom::_cupons_criados = 0;

Cupom::Cupom(std::string etiqueta, double desconto, int idDoCliente)
{
  _etiqueta = etiqueta;
  _valor_desconto = desconto;
  _valido = true;
  _idDoCliente = idDoCliente;
}

double Cupom::GetValor()
{
  return _valor_desconto;
}

std::string Cupom::GetEtiqueta()
{
  return _etiqueta;
}
    
bool Cupom::EstaValido(){
  return _valido;
}

void Cupom::SetaValido(){
  _valido = false;
}

int Cupom::GetIdDoCliente()
{
  return _idDoCliente;
}