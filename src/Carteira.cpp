#include "Carteira.hpp"

Carteira::Carteira(int idCliente)
{
  _idCliente = idCliente;
  _saldo = 0.0;
}

int Carteira::GetIdCliente(){
  return _idCliente;
}

double Carteira::GetSaldo(){
  return _saldo;
}

void Carteira::SetSaldo(double saldo){
  _saldo = saldo;
}

void Carteira::AdicionarSaldo(double saldo){
  if(saldo <= 0){
    throw impossivel_adicionar_saldo_negativo_ou_igual_a_zero_e();
  }

  _saldo += saldo;
}

void Carteira::RemoverSaldo(double saldo){
  if(saldo == 0){
    throw sem_saldo_e();
  }

 if(saldo <= 0){
    throw impossivel_remover_saldo_negativo_ou_igual_a_zero_e();
  }

  if(_saldo < saldo){
    throw saldo_insuficiente_para_remocao_e();
  }

  _saldo -= saldo;
}