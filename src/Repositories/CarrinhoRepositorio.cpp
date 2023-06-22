#include <map>
#include <vector>
#include <variant>

#include "Cliente.hpp"
#include "Carrinho.hpp"
#include "Sqlite/sqlite3.h"
#include "Repositories/CarrinhoRepositorio.hpp"

CarrinhoRepositorio::CarrinhoRepositorio()
{ }

Carrinho* CarrinhoRepositorio::ConverterParaEntidade(sqlite3_stmt* stmt)
{    
    int id = sqlite3_column_int(stmt, 0);
    std::string criacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    std::string atualizacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));

    int idCliente = sqlite3_column_int(stmt, 1);
    
    double valorTotal = sqlite3_column_double(stmt, 4);
    bool encerrado = sqlite3_column_int(stmt, 5);

    Carrinho* entidade = new Carrinho(idCliente);
    entidade->SetarDadosBase(criacao, atualizacao, id);
    entidade->SetValorTotal(valorTotal);
    entidade->SetStatus(encerrado);

    return entidade;
}

Carrinho* CarrinhoRepositorio::BuscaPorId(int id)
{
    return RepositorioBase::BuscaPorId(_tabela, id);
}

std::vector<Carrinho*> CarrinhoRepositorio::BuscaPorIdDoCliente(int idCliente)
{
    std::string idClienteString = std::to_string(idCliente);
    std::string where = "WHERE IdCliente = " + idClienteString;

    RepositorioBase::CarregarTodosOsDadosNaMemoria(_tabela, where);

    std::vector<Carrinho*> carrinhos;
    for(auto pair : _entidades)
    {
        Carrinho* atual = pair.second;
        if (atual->GetIdCliente() == idCliente)
        {
            carrinhos.push_back(atual);
        }
    }   

    return carrinhos;
}

void CarrinhoRepositorio::Inserir(Carrinho* entidade)
{
    std::string query = "INSERT INTO " + _tabela + " (idCliente, dataDeCriacao, dataUltimaAtualizacao, valorTotal, pedidoEncerrado) VALUES ({0}, '{1}', '{2}', {3}, {4});";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entidade->GetIdCliente() },
        { "{1}", entidade->GetDataDeCriacao() },
        { "{2}", entidade->GetDataUltimaAtualizacao() },
        { "{3}", entidade->GetValorTotal() },
        { "{4}", entidade->EstaEncerrado() }
    };        

    ExecuteSQLReplace(query, values);
    InserirNovoRegistro(entidade);
}

void CarrinhoRepositorio::Atualizar(Carrinho* entidade)
{
    entidade->AtualizarAgora();

    std::string query = "UPDATE " + _tabela + " SET valorTotal = {0}, dataUltimaAtualizacao = '{1}', pedidoEncerrado = {2} WHERE id = {3};";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entidade->GetValorTotal() },
        { "{1}", entidade->GetDataUltimaAtualizacao() },
        { "{2}", entidade->EstaEncerrado() },
        { "{3}", entidade->GetId() }
    };        

    ExecuteSQLReplace(query, values);
}

void CarrinhoRepositorio::Deletar(Carrinho* entidade)
{
    RepositorioBase::Deletar(_tabela, entidade);
}

void CarrinhoRepositorio::CreateTable()
{
    std::string query = "CREATE TABLE IF NOT EXISTS " + _tabela + " ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "idCliente INTEGER,"
                        "dataDeCriacao TEXT,"
                        "dataUltimaAtualizacao TEXT,"
                        "valorTotal REAL,"
                        "pedidoEncerrado INTEGER"
                        ");";

    ExecuteSQL(query);
}