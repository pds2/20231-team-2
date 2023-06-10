#pragma once

#ifndef ENTIDADE_BASE_HPP
#define ENTIDADE_BASE_HPP

#include <string>

/*
 *  Essa classe é responsável por armazenar e inicializar as informações básicas
 * comuns a todas entidades que serão mapeadas para o banco de dados da aplicação.
 */
class EntidadeBase
{
    private:
        int _id;
        std::string _dataDeCriacao;
        std::string _dataUltimaAtualizacao;
    public:
        /**
         * @brief Instância de uma nova entidade.
         */
        EntidadeBase();

        /**
         * @brief Retorna o identificador da entidade.
         */
        int GetId();

        /**
         * @brief Retorna a data de criação da entidade.
         */
        std::string GetDataDeCriacao();
        
        /**
         * @brief Retorna a data da útlima alteração da entidade.
         */
        std::string GetDataUltimaAtualizacao();    

        /**
         * @brief Atualiza a data da última alteração da entidade para a data atual.
         */
        void AtualizarAgora();

        /**
         * @brief Atualiza todos os dados da entidade.
         */
        void SetarDadosBase(std::string dataCriacao, std::string dataAtualizacao, int id);
};

#endif