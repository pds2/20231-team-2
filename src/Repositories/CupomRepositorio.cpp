#include <map>
#include <vector>
#include <variant>

#include "Cupom.hpp"
#include "Cliente.hpp"
#include "CupomBasico.hpp"
#include "CupomCustomizado.hpp"
#include "Sqlite/sqlite3.h"
#include "Repositories/CupomRepositorio.hpp"

CupomRepositorio::CupomRepositorio()
{ 
    CreateTable();
}

Cupom* CupomRepositorio::ConverterParaEntidade(sqlite3_stmt* stmt)
{    
    int id = sqlite3_column_int(stmt, 0);
    int idCliente = sqlite3_column_int(stmt, 1);

    std::string criacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
    std::string atualizacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
    
    int valido = sqlite3_column_int(stmt, 2);
    double desconto = sqlite3_column_double(stmt, 3);

    std::string descricao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
    std::string etiqueta(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));

    CupomType tipo = static_cast<CupomType>(sqlite3_column_int(stmt, 6));

    Cupom* entidade;

    if (tipo == CupomType::BASICO)
    {
        entidade = new CupomBasico(etiqueta, desconto, idCliente);
    }
    else
    {
        entidade = new CupomCustomizado(etiqueta, desconto, idCliente, descricao);
    }

    entidade->SetarDadosBase(criacao, atualizacao, id);

    if(!valido)
        entidade->SetaInvalido();

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

void CupomRepositorio::CarregarCuponsNoCliente(Cliente* cliente)
{
    int idCliente = cliente->GetId();
    std::string idClienteString = std::to_string(idCliente);

    std::string where = "WHERE idCliente = " + idClienteString;
    RepositorioBase::CarregarTodosOsDadosNaMemoria(_tabela);

    std::vector<Cupom*> cupons;
    for(auto par : _entidades)
    {
        Cupom* cupom = par.second;
        if (cupom->GetIdDoCliente() == idCliente)
            cupons.push_back(cupom);
    }

    cliente->SetCupons(cupons);
}

Cupom* CupomRepositorio::BuscaPorId(int id)
{
    return RepositorioBase::BuscaPorId(_tabela, id);
}

void CupomRepositorio::Inserir(Cupom* entidade)
{
    std::string query = "INSERT INTO " + _tabela + " (idCliente, valido, valor_desconto, descricao, etiqueta, tipo, dataDeCriacao, dataUltimaAtualizacao) VALUES ({0}, {1}, {2}, '{3}', '{4}', {5} ,'{6}', '{7}');";
    
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entidade->GetIdDoCliente() },
        { "{1}", static_cast<int>(entidade->EstaValido()) },
        { "{2}", entidade->GetValor() },
        { "{3}", entidade->Descricao() },
        { "{4}", entidade->GetEtiqueta() },
        { "{5}", static_cast<int>(entidade->GetTipoCupom()) },
        { "{6}", entidade->GetDataDeCriacao() },
        { "{7}", entidade->GetDataUltimaAtualizacao() }
    };

    ExecuteSQLReplace(query, values);
    InserirNovoRegistro(entidade);
}

void CupomRepositorio::Atualizar(Cupom* entidade)
{
    entidade->AtualizarAgora();

    std::string query = "UPDATE " + _tabela + " SET valido = {0}, valor_desconto = {1}, descricao = '{2}', etiqueta = '{3}', dataUltimaAtualizacao = '{4}' WHERE id = {5};";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entidade->EstaValido() },
        { "{1}", entidade->GetValor() },
        { "{2}", entidade->Descricao() },
        { "{3}", entidade->GetEtiqueta() },
        { "{4}", entidade->GetDataUltimaAtualizacao() },
        { "{5}", entidade->GetId() },
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
                        "idCliente INTEGER,"
                        "valido INT,"
                        "valor_desconto REAL,"
                        "descricao TEXT,"
                        "etiqueta TEXT,"
                        "tipo INT,"
                        "dataDeCriacao TEXT,"
                        "dataUltimaAtualizacao TEXT);";

    ExecuteSQL(query);
}