#pragma once

#ifndef CARTEIRAREPOSITORIO_HPP
#define CARTEIRAREPOSITORIO_HPP

#include "../Carteira.hpp"
#include "RepositorioBase.hpp"

/*
 * Repositório que permite o acesso as carteiras armazenadas no banco de dados.
 */
class CarteiraRepositorio 
    : RepositorioBase<Carteira>
{
    private:
        std::string _tabela = "Carteira";

        /**
         * @brief Executa o comando para criar a tabela desse repositório no banco de dados.
        */
        void CreateTable();
        
        /**
         * @brief Converte um objeto retornado pelo banco de dados em um ponteiro.
         * @returns Um ponteiro pro objeto definitivo.
        */
        Carteira* ConverterParaEntidade(sqlite3_stmt* stmt);

    public:   
        /**
         * @brief Instância uma nova comunicação de uma entidade com o banco de dados.
         */
        CarteiraRepositorio();

        /**
         * @brief Busca um objeto no banco de dados.
         * @param id Id do objeto buscado.
         * @returns Um ponteiro para o objeto buscado.
         */
        Carteira* BuscaPorId(int id);

        /**
         * @brief Insere um objeto no banco de dados.
         * @param entity Objeto que será inserido.
         */
        void Inserir(Carteira* entidade);

        /**
         * @brief Atualiza um objeto do banco de dados.
         * @param entity Objeto que será atualizado.
         */
        void Atualizar(Carteira* entidade);
        
        /**
         * @brief Deleta um objeto do banco de dados.
         * @param entity Objeto que será deletado.
         */
        void Deletar(Carteira* entidade);
};

#endif