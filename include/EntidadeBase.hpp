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
        unsigned int _id;
        std::string _dataDeCriacao;
        std::string _dataUltimaAtualizacao;
    public:
        /*
         * @brief Instância de uma nova entidade.
         */
        EntidadeBase(unsigned int id);

        /*
         * @brief Retorna o identificador da entidade.
         */
        unsigned int GetId();

        /*
         * @brief Retorna a data de criação da entidade.
         */
        std::string GetDataDeCriacao();
        
        /*
         * @brief Retorna a data da útlima alteração da entidade.
         */
        std::string GetDataUltimaAtualizacao();    

        /*
         * @brief Atualiza a data da última alteração da entidade para a data atual.
         */
        void AtualizarAgora();
};

#endif