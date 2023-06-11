#include <ctime>
#include <string>

#include "../include/EntidadeBase.hpp"

std::string GetDataAtual()
{
    // Obtém o tempo atual
    std::time_t tempoAtual = std::time(nullptr);

    // Converte o tempo atual em uma estrutura tm (para obter os componentes da data/hora)
    std::tm* tempoLocal = std::localtime(&tempoAtual);

    // Formata a data atual no formato desejado
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%H:%M %d/%m/%Y", tempoLocal);

    // Retorna a data formatada como uma string
    return std::string(buffer);
}

EntidadeBase::EntidadeBase()
{
    _dataDeCriacao = GetDataAtual();
    _dataUltimaAtualizacao = "00:00 01/01/0001";
}

int EntidadeBase::GetId()
{
    return _id;
}

void EntidadeBase::SetId(int id)
{
    _id = id;
}

std::string EntidadeBase::GetDataDeCriacao()
{
    return _dataDeCriacao;
}

std::string EntidadeBase::GetDataUltimaAtualizacao()
{
    return _dataUltimaAtualizacao;
}

void EntidadeBase::AtualizarAgora()
{
    _dataUltimaAtualizacao = GetDataAtual();
}

void EntidadeBase::SetarDadosBase(std::string dataCriacao, std::string dataAtualizacao, int id)
{
    _id = id;
    _dataDeCriacao = dataCriacao;
    _dataUltimaAtualizacao = dataAtualizacao;
}