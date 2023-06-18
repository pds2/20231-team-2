#include "../include/Carteira.hpp"

Carteira::Carteira(std::string nomeDoCliente)
{
  _nomeDoCliente = nomeDoCliente;
  _saldo = 0.0;
}

std::string Carteira::GetNome(){
  return _nomeDoCliente;
}

double Carteira::GetSaldo(){
  return _saldo;
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