#include <map>
#include <vector>
#include <variant>

#include "Restaurante.hpp"
#include "Sqlite/sqlite3.h"
#include "Repositories/RestauranteRepositorio.hpp"

RestauranteRepositorio::RestauranteRepositorio(ItemRepositorio* itemRepositorio)
{
    _itemRepositorio = itemRepositorio;

    CreateTable();
}

Restaurante* RestauranteRepositorio::ConverterParaEntidade(sqlite3_stmt* stmt)
{    
    int id = sqlite3_column_int(stmt, 0);
    std::string criacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    std::string atualizacao(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));

    std::string cnpj(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
    std::string nome(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
    std::string login(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
    std::string senha(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));

    Restaurante* entity = new Restaurante(nome, login, senha, cnpj);
    entity->SetarDadosBase(criacao, atualizacao, id);

    return entity;
}

std::vector<Restaurante*> RestauranteRepositorio::ListarTodos()
{
    RepositorioBase::CarregarTodosOsDadosNaMemoria(_tabela);

    std::vector<Restaurante*> itens;

    for(auto pair : _entidades)
    {
        Restaurante* entidade = pair.second;
        _itemRepositorio->CarregarItensNoRestaurante(entidade);

        itens.push_back(entidade);
    }

    return itens;
}

Restaurante* RestauranteRepositorio::BuscaPorId(int id)
{
    Restaurante* entidade = RepositorioBase::BuscaPorId(_tabela, id);
    _itemRepositorio->CarregarItensNoRestaurante(entidade);

    return entidade;
}

Restaurante* RestauranteRepositorio::BuscaPorLogin(std::string login)
{
    RepositorioBase::CarregarTodosOsDadosNaMemoria(_tabela, "");

    for(auto pair : _entidades)
    {
        Restaurante* restaurante = pair.second;
        if (restaurante->GetLogin() == login)
            return restaurante;
    }

    throw login_nao_encontrado_e();
}

void RestauranteRepositorio::Inserir(Restaurante* entidade)
{
    std::string query = "INSERT INTO " + _tabela + " (nome, dataDeCriacao, dataUltimaAtualizacao, cnpj, nome, login, senha) VALUES ('{0}', '{1}', '{2}', '{3}', '{4}', '{5}', '{6}');";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entidade->GetNome() },
        { "{1}", entidade->GetDataDeCriacao() },
        { "{2}", entidade->GetDataUltimaAtualizacao() },
        { "{3}", entidade->GetCNPJ() },
        { "{4}", entidade->GetNome() },
        { "{5}", entidade->GetLogin() },
        { "{6}", entidade->GetSenha() },
    };        

    ExecuteSQLReplace(query, values);
    InserirNovoRegistro(entidade);

    for(Item* item : entidade->GetItens())
        _itemRepositorio->Inserir(item);
}

void RestauranteRepositorio::Atualizar(Restaurante* entidade)
{
    entidade->AtualizarAgora();
    
    std::string query = "UPDATE " + _tabela + " SET nome = '{0}', dataUltimaAtualizacao = '{1}', cnpj = '{2}', login = '{3}', senha = '{4}' WHERE id = {5};";
    std::map<std::string, std::variant<int, double, std::string>> values = 
    {
        { "{0}", entidade->GetNome() },
        { "{1}", entidade->GetDataUltimaAtualizacao() },
        { "{2}", entidade->GetCNPJ() },
        { "{3}", entidade->GetLogin() },
        { "{4}", entidade->GetSenha() },
        { "{5}", entidade->GetId() },
    };

    ExecuteSQLReplace(query, values);
}

void RestauranteRepositorio::Deletar(Restaurante* entidade)
{
    for(Item* item : entidade->GetItens())
        _itemRepositorio->Deletar(item);

    RepositorioBase::Deletar(_tabela, entidade);
}

void RestauranteRepositorio::CreateTable()
{
    std::string query = "CREATE TABLE IF NOT EXISTS " + _tabela + " ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "dataDeCriacao TEXT,"
                        "dataUltimaAtualizacao TEXT,"
                        "cnpj TEXT,"
                        "nome TEXT,"
                        "login TEXT,"
                        "senha TEXT"
                        ");";

    ExecuteSQL(query);
}