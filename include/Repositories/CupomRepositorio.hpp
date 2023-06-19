#pragma once

#ifndef CUPOMREPOSITORIO_HPP
#define CUPOMREPOSITORIO_HPP

#include "../Cupom.hpp"
#include "RepositorioBase.hpp"

/*
 * Repositório que permite o acesso aos itens armazenados no banco de dados.
 */
class CupomRepositorio 
    : RepositorioBase<Cupom>
{
    private:
        std::string _tabela = "Cupom";

        /**
         * @brief Executa o comando para criar a tabela desse repositório no banco de dados.
        */
        void CreateTable();
        
        /**
         * @brief Converte um objeto retornado pelo banco de dados em um ponteiro.
         * @returns Um ponteiro pro objeto definitivo.
        */
        Cupom* ConverterParaEntidade(sqlite3_stmt* stmt);

    public:   
        /**
         * @brief Instância uma nova comunicação de uma entidade com o banco de dados.
         */
        CupomRepositorio();

        /**
         * @brief Lista os objetos salvos no banco de dados.
         * @returns Uma lista de ponteiros para o objetos armazenados.
         */
        std::vector<Cupom*> ListarTodos();

        /**
         * @brief Busca um objeto no banco de dados.
         * @param id Id do objeto buscado.
         * @returns Um ponteiro para o objeto buscado.
         */
        Cupom* BuscaPorId(int id);

        /**
         * @brief Insere um objeto no banco de dados.
         * @param entity Objeto que será inserido.
         */
        void Inserir(Cupom* entidade);

        /**
         * @brief Atualiza um objeto do banco de dados.
         * @param entity Objeto que será atualizado.
         */
        void Atualizar(Cupom* entidade);
        
        /**
         * @brief Deleta um objeto do banco de dados.
         * @param entity Objeto que será deletado.
         */
        void Deletar(Cupom* entidade);
};

#endif