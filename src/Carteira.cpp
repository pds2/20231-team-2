#include "../include/Carteira.hpp"

Carteira::Carteira(std::string nomeDoCliente){
  _nomeDoCliente = nomeDoCliente;
  _saldo = 0.0
}

std::string Carteira::get_nome(){
  return _nomeDoCliente;
}

double Carteira::get_saldo(){
  return _saldo;
}

void Carteira::adicionar_saldo(double saldo){
  if(saldo <= 0){
    throw impossivel_adicionar_saldo_negativo_ou_igual_a_zero_e();
  }

  _saldo += saldo;
}

void Carteira::remover_saldo(double saldo){
 if(saldo <= 0){
    throw impossivel_remover_saldo_negativo_ou_igual_a_zero_e();
  }

  if(_saldo < saldo){
    throw saldo_insuficiente_para_remocao_e();
  }

  _saldo -= saldo;
}