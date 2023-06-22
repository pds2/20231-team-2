#include <map>
#include <vector>
#include <variant>

#include "Cupom.hpp"
#include "Sqlite/sqlite3.h"
#include "Repositories/CupomRepositorio.hpp"

CupomRepositorio::CupomRepositorio()
{ }

Cupom* CupomRepositorio::ConverterParaEntidade(sqlite3_stmt* stmt)
{    
    int id = sqlite3_column_int(stmt, 0);
    std::string criacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
    std::string atualizacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));

    std::string codigo(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    std::string expiracao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));

    float desconto = sqlite3_column_double(stmt, 2);

    Cupom* entidade = new Cupom(codigo, desconto);
    entidade->SetarDadosBase(criacao, atualizacao, id);

    return entidade;
}

std::vector<Cupom*> CupomRepositorio::ListarTodos()
{
    RepositorioBase::CarregarTodosOsDadosNaMemoria(_tabela);

    std::vector<Cupom*> itens;

    for(auto pair : _entidades)
    {
        itens.push_back(pair.second);
    }

    return itens;
}

Cupom* CupomRepositorio::BuscaPorId(int id)
{
    return RepositorioBase::BuscaPorId(_tabela, id);
}

void CupomRepositorio::Inserir(Cupom* entidade)
{
    std::string query = "INSERT INTO " + _tabela + " (codigo, desconto, expiracao, dataDeCriacao, dataUltimaAtualizacao) VALUES ('{0}', {1}, '{2}', '{3}', '{4}');";
    
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entidade->GetCodigo() },
        { "{1}", entidade->GetValor() },
        { "{2}", entidade->GetDataDeExpiracao() },
        { "{3}", entidade->GetDataDeCriacao() },
        { "{4}", entidade->GetDataUltimaAtualizacao() }
    };

    ExecuteSQLReplace(query, values);
    InserirNovoRegistro(entidade);
}

void CupomRepositorio::Atualizar(Cupom* entidade)
{
    entidade->AtualizarAgora();

    std::string query = "UPDATE " + _tabela + " SET codigo = '{0}', desconto = {1}, expiracao = '{2}', dataUltimaAtualizacao = '{3}' WHERE id = {4};";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entidade->GetCodigo() },
        { "{1}", entidade->GetValor() },
        { "{2}", entidade->GetDataDeExpiracao() },
        { "{3}", entidade->GetDataUltimaAtualizacao() },
        { "{4}", entidade->GetId() }
    };

    ExecuteSQLReplace(query, values);
}

void CupomRepositorio::Deletar(Cupom* entidade)
{
    RepositorioBase::Deletar(_tabela, entidade);
}

void CupomRepositorio::CreateTable()
{
    std::string query = "CREATE TABLE IF NOT EXISTS " + _tabela + " ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "codigo TEXT,"
                        "desconto REAL,"
                        "expiracao TEXT,"
                        "dataDeCriacao TEXT,"
                        "dataUltimaAtualizacao TEXT);";

    ExecuteSQL(query);
}