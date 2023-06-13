#include <map>
#include <vector>
#include <variant>

#include "../../include/Cliente.hpp"
#include "../../libs/sqllite/sqlite3.h"
#include "../../include/Repositories/ClienteRepositorio.hpp"

ClienteRepositorio::ClienteRepositorio()
{
    CreateTable();
}

EntidadeBase* ClienteRepositorio::ConverterParaEntidade(sqlite3_stmt* stmt)
{    
    int id = sqlite3_column_int(stmt, 0);
    std::string criacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    std::string atualizacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));

    std::string cpf(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
    std::string nome(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
    std::string login(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
    std::string senha(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));

    Cliente* entity = new Cliente(nome, login, senha, cpf);
    entity->SetarDadosBase(criacao, atualizacao, id);

    return entity;

}

Cliente* ClienteRepositorio::Cast(EntidadeBase* entidadeBase)
{
    return dynamic_cast<Cliente*>(entidadeBase);
}

std::vector<Cliente*> ClienteRepositorio::ListarTodos()
{
    RepositorioBase::CarregarTodosOsDadosNaMemoria(_tabela);

    std::vector<Cliente*> itens;

    for(auto pair : _entidades)
    {
        itens.push_back(Cast(pair.second));
    }

    return itens;
}

Cliente* ClienteRepositorio::BuscaPorId(int id)
{
    EntidadeBase* baseComum = RepositorioBase::BuscaPorId(_tabela, id);
    return Cast(baseComum);
}

void ClienteRepositorio::Inserir(Cliente* entidade)
{
    std::string query = "INSERT INTO " + _tabela + " (nome, dataDeCriacao, dataUltimaAtualizacao, cpf, nome, login, senha) VALUES ('{0}', '{1}', '{2}', '{3}', '{4}', '{5}', '{6}');";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entidade->GetNome() },
        { "{1}", entidade->GetDataDeCriacao() },
        { "{2}", entidade->GetDataUltimaAtualizacao() },
        { "{3}", entidade->GetCPF() },
        { "{4}", entidade->GetNome() },
        { "{5}", entidade->GetLogin() },
        { "{6}", entidade->GetSenha() },
    };        

    ExecuteSQLReplace(query, values);
    InserirNovoRegistro(entidade);
}

void ClienteRepositorio::Atualizar(Cliente* entidade)
{
    entidade->AtualizarAgora();
    
    std::string query = "UPDATE " + _tabela + " SET nome = '{0}', dataUltimaAtualizacao = '{1}', cpf = '{2}', login = '{3}', senha = '{4}' WHERE id = {5};";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entidade->GetNome() },
        { "{1}", entidade->GetDataUltimaAtualizacao() },
        { "{2}", entidade->GetCPF() },
        { "{3}", entidade->GetLogin() },
        { "{4}", entidade->GetSenha() },
        { "{5}", entidade->GetId() },
    };

    ExecuteSQLReplace(query, values);
}

void ClienteRepositorio::Deletar(Cliente* entidade)
{
    RepositorioBase::Deletar(_tabela, entidade);
}

void ClienteRepositorio::CreateTable()
{
    std::string query = "CREATE TABLE IF NOT EXISTS " + _tabela + " ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "dataDeCriacao TEXT,"
                        "dataUltimaAtualizacao TEXT,"
                        "cpf TEXT,"
                        "nome TEXT,"
                        "login TEXT,"
                        "senha TEXT"
                        ");";

    ExecuteSQL(query);
}