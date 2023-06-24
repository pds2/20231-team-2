#include "Repositories/DatabaseManager.hpp"
#include "Repositories/ItemRepositorio.hpp"
#include "Repositories/CupomRepositorio.hpp"
#include "Repositories/ClienteRepositorio.hpp"
#include "Repositories/CarteiraRepositorio.hpp"
#include "Repositories/RestauranteRepositorio.hpp"

DatabaseManager::DatabaseManager()
{
    _itemRepositorio = new ItemRepositorio();
    _cupomRepositorio = new CupomRepositorio();
    _carteiraRepositorio = new CarteiraRepositorio();
    _itemCarrinhoRepositorio = new ItemCarrinhoRepositorio(_itemRepositorio);
    _carrinhoRepositorio = new CarrinhoRepositorio(_itemCarrinhoRepositorio);
    _clienteRepositorio = new ClienteRepositorio(_carteiraRepositorio, _carrinhoRepositorio);
    _restauranteRepositorio = new RestauranteRepositorio(_itemRepositorio, _itemCarrinhoRepositorio);
}

DatabaseManager::~DatabaseManager()
{
    delete _itemRepositorio;
    delete _cupomRepositorio;
    delete _clienteRepositorio;
    delete _carteiraRepositorio;
    delete _itemCarrinhoRepositorio;
    delete _carrinhoRepositorio;
    delete _restauranteRepositorio;
}

ItemRepositorio* DatabaseManager::GetItemRepositorio()
{
    return _itemRepositorio;
}

CupomRepositorio* DatabaseManager::GetCupomRepositorio()
{
    return _cupomRepositorio;
}

ClienteRepositorio* DatabaseManager::GetClienteRepositorio()
{
    return _clienteRepositorio;
}

CarteiraRepositorio* DatabaseManager::GetCarteiraRepositorio()
{
    return _carteiraRepositorio;
}

RestauranteRepositorio* DatabaseManager::GetRestauranteRepositorio()
{
    return _restauranteRepositorio;
}

CarrinhoRepositorio* DatabaseManager::GetCarrinhoRepositorio()
{
    return _carrinhoRepositorio;
}