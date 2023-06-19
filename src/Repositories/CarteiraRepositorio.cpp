#include <map>
#include <vector>
#include <variant>

#include "../../include/Carteira.hpp"
#include "../../libs/sqllite/sqlite3.h"
#include "../../include/Cliente.hpp"
#include "../../include/Repositories/CarteiraRepositorio.hpp"

CarteiraRepositorio::CarteiraRepositorio()
{
    CreateTable();
}

Carteira* CarteiraRepositorio::ConverterParaEntidade(sqlite3_stmt* stmt)
{    
    int id = sqlite3_column_int(stmt, 0);
    std::string criacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
    std::string atualizacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));

    double saldo = sqlite3_column_double(stmt, 2);
    int idCliente = sqlite3_column_double(stmt, 1);

    Carteira* entidade = new Carteira(idCliente);

    entidade->SetSaldo(saldo);
    entidade->SetarDadosBase(criacao, atualizacao, id);

    return entidade;
}

Carteira* CarteiraRepositorio::BuscaPorId(int id)
{
    return RepositorioBase::BuscaPorId(_tabela, id);
}

Carteira* CarteiraRepositorio::BuscaPorIdDoCliente(int idCliente)
{
    std::string idClienteString = std::to_string(idCliente);
    std::string where = "WHERE IdCliente = " + idClienteString;

    RepositorioBase::CarregarTodosOsDadosNaMemoria(_tabela);

    for(auto pair : _entidades)
    {
        Carteira* atual = pair.second;
        if (atual->GetIdCliente() == idCliente)
        {
            return atual;
        }
    }   

    return nullptr;
}

void CarteiraRepositorio::Inserir(Carteira* entidade)
{
    std::string query = "INSERT INTO " + _tabela + " (idCliente, saldo, dataDeCriacao, dataUltimaAtualizacao) VALUES ({0}, {1}, '{2}', '{3}');";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{1}", entidade->GetIdCliente() },
        { "{1}", entidade->GetSaldo() },
        { "{2}", entidade->GetDataDeCriacao() },
        { "{4}", entidade->GetDataUltimaAtualizacao() }
    };        

    ExecuteSQLReplace(query, values);
    InserirNovoRegistro(entidade);
}

void CarteiraRepositorio::Atualizar(Carteira* entidade)
{
    entidade->AtualizarAgora();

    std::string query = "UPDATE " + _tabela + " SET saldo = '{0}', idCliente = {1}, dataUltimaAtualizacao = '{2}' WHERE id = {3};";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entidade->GetSaldo() },
        { "{1}", entidade->GetIdCliente() },
        { "{2}", entidade->GetDataUltimaAtualizacao() },
        { "{3}", entidade->GetDataUltimaAtualizacao() },
        { "{4}", entidade->GetId() }
    };        

    ExecuteSQLReplace(query, values);
}

void CarteiraRepositorio::Deletar(Carteira* entidade)
{
    RepositorioBase::Deletar(_tabela, entidade);
}

void CarteiraRepositorio::CreateTable()
{
    std::string query = "CREATE TABLE IF NOT EXISTS " + _tabela + " ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "idCliente INTEGER,"
                        "saldo REAL,"
                        "dataDeCriacao TEXT,"
                        "dataUltimaAtualizacao TEXT);";

    ExecuteSQL(query);
}