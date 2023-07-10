#pragma once

#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>
#include <vector>

#include "Usuario.hpp"
#include "Carteira.hpp"
#include "Carrinho.hpp"
#include "Cupom.hpp"

/**
 * @brief Lança uma exceção se o cliente tentar usar um cupom
 * que não existe/que não tem.
*/
class cupom_nao_existe_e {};

/**
 * @class Cliente
 * @brief Classe que representa um cliente.
 *
 * Essa classe é responsável por armazenar e inicializar as informações básicas
 * de um usuário do tipo cliente.
 */
class Cliente : public Usuario {
private:
    Carteira* _carteira;
    std::vector<Carrinho*> _carrinhos;
    std::vector<Cupom*> _cupons;

public:
    /**
     * @brief Construtor da classe Cliente.
     * @param nome O nome do cliente.
     * @param login O login do cliente.
     * @param senha A senha do cliente.
     * @param CPF O CPF do cliente.
     */
    Cliente(std::string nome, std::string login, std::string senha, std::string CPF);

    /**
     * @brief Retorna um ponteiro para a carteira desse cliente.
     * @return O ponteiro para a carteira do cliente.
     */
    Carteira* GetCarteira();

    /**
     * @brief Define a carteira desse cliente.
     * @param carteira O ponteiro para a carteira do cliente.
     */
    void SetCarteira(Carteira* carteira);

    /**
     * @brief Adiciona um carrinho a esse cliente.
     * @param carrinho O carrinho a ser adicionado.
     */
    void AdicionarCarrinho(Carrinho* carrinho);

    /**
     * @brief Remove um carrinho desse cliente.
     * @param carrinho O carrinho a ser removido.
     */
    void RemoverCarrinho(Carrinho* carrinho);

    /**
     * @brief Retorna os carrinhos desse cliente.
     * @return Um vetor de ponteiros para os carrinhos do cliente.
     */
    std::vector<Carrinho*> GetCarrinhos();

    /**
     * @brief Define os carrinhos desse cliente.
     * @param carrinhos O vetor de ponteiros para os carrinhos do cliente.
     */
    void SetCarrinhos(std::vector<Carrinho*> carrinhos);

    /**
     * @brief Retorna o tipo do usuário, neste caso, cliente.
     * @return O tipo do usuário.
     */
    TipoUsuario GetTipo() override;

    /**
     * @brief Adiciona um cupom aos cupons do cliente.
     * @param cupom O ponteiro para os cupons do cliente.
    */
    void AdicionaCupom(Cupom* cupom);

    /**
     * @brief Retorna o vetor de Cupons que o cliente possui.
     * @return Um vetor de ponteiros para os cupons do cliente.
    */
    std::vector<Cupom*> GetCupons();

    /**
     * @brief Seta os cupons desse cliente.
     * @param cupons novo vector de cupons.
    */
    void SetCupons(std::vector<Cupom*> cupons);

    /**
     * @brief Retorna o cupom ao qual o id se refere.
     * @param id Id do cupom.
     * @return Ponteiro para cupom.
    */
    Cupom* GetCupom(int id);

    /**
     * @brief Responsável por validar se o CPF informado é válido.
     * @param documento CPF a ser validado.
     * @returns true caso sejá válido.
    */
    bool DocumentoValido(std::string documento) override;

    /**
     * @brief Responsável por formatar o CPF informado.
     * @param documento CPF a ser formatado.
     * @returns CPF com a formatação correta.
    */
    std::string FormatarDocumento(std::string documento) override;
};

#endif // CLIENTE_HPP
