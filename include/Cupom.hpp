#ifndef CUPOM_HPP
#define CUPOM_HPP

#include <string>

#include "EntidadeBase.hpp"

/*
 *@brief Essa classe representa um cupom que poderá ser usado
 *para que o cliente tenha desconto nas compras.
 */
class Cupom: public EntidadeBase{
  private:
  std::string _codigo;
  double _desconto;
  bool _valido;
  //poderá ser definido mais tarde
  std::string _dataExpiracao;

  public:
  /*
   *@brief Cria um novo cupom de desconto
   */
  Cupom(std::string codigo, double desconto);

  /*
   * @brief Retorna o código do cupom de desconto 
   */
  std::string GetCodigo();

  /*
   * @brief Retorna o valor do cupom de desconto 
   */
  double GetValor();

  std::string GetDataDeExpiracao();
  
  /*
   * @brief Verifica se o código está dentro da 
   * data de expiração 
   */
  bool EstaValido();

};

#endif