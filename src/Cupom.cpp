#include <string>

#include "Cupom.hpp"

Cupom::Cupom(std::string etiqueta, double desconto, int idDoCliente, CupomType tipo)
{

  if(desconto <= 0){
    throw impossivel_desconto_negativo_e();
  }

  _etiqueta = etiqueta;
  _valor_desconto = desconto;
  _valido = true;
  _idDoCliente = idDoCliente;
  _tipo = tipo;
}

double Cupom::GetValor()
{
  return _valor_desconto;
}

std::string Cupom::GetEtiqueta()
{
  return _etiqueta;
}

CupomType Cupom::GetTipoCupom(){
  return _tipo;
}
    
bool Cupom::EstaValido(){
  return _valido;
}

void Cupom::SetaInvalido(){
  _valido = false;
}

int Cupom::GetIdDoCliente()
{
  return _idDoCliente;
}