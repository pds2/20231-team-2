#pragma once

#ifndef ENTIDADE_BASE_HPP
#define ENTIDADE_BASE_HPP

#include <string>

/**
 * @class EntidadeBase
 * @brief Classe base para entidades mapeadas no banco de dados.
 *
 * Essa classe é responsável por armazenar e inicializar as informações básicas comuns a todas as entidades que serão mapeadas para o banco de dados da aplicação.
 */
class EntidadeBase
{
private:
    int _id;
    std::string _dataDeCriacao;
    std::string _dataUltimaAtualizacao;

public:
    /**
     * @brief Construtor da classe EntidadeBase.
     */
    EntidadeBase();

    /**
     * @brief Destrutor de uma entidade.
     */
    virtual ~EntidadeBase();

    /**
     * @brief Retorna o identificador da entidade.
     * @return O identificador da entidade.
     */
    int GetId();

    /**
     * @brief Atualiza o identificador da entidade.
     * @param id O novo identificador da entidade.
     */
    void SetId(int id);

    /**
     * @brief Retorna a data de criação da entidade.
     * @return A data de criação da entidade.
     */
    std::string GetDataDeCriacao();

    /**
     * @brief Retorna a data da última atualização da entidade.
     * @return A data da última atualização da entidade.
     */
    std::string GetDataUltimaAtualizacao();

    /**
     * @brief Atualiza a data da última atualização da entidade para a data atual.
     */
    virtual void AtualizarAgora();

    /**
     * @brief Define os dados básicos da entidade.
     * @param dataCriacao A data de criação da entidade.
     * @param dataAtualizacao A data da última atualização da entidade.
     * @param id O identificador da entidade.
     */
    void SetarDadosBase(std::string dataCriacao, std::string dataAtualizacao, int id);
};

#endif // ENTIDADE_BASE_HPP
