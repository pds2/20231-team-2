#include "DatabaseManager.hpp"
#include "ItemRepositorio.hpp"
#include "CupomRepositorio.hpp"
#include "ClienteRepositorio.hpp"
#include "CarteiraRepositorio.hpp"
#include "RestauranteRepositorio.hpp"

DatabaseManager::DatabaseManager()
{
    _itemRepositorio = new ItemRepositorio();
    _cupomRepositorio = new CupomRepositorio();
    _carteiraRepositorio = new CarteiraRepositorio();
    _clienteRepositorio = new ClienteRepositorio(_carteiraRepositorio);
    _restauranteRepositorio = new RestauranteRepositorio(_itemRepositorio);
}

DatabaseManager::~DatabaseManager()
{
    delete _itemRepositorio;
    delete _cupomRepositorio;
    delete _clienteRepositorio;
    delete _carteiraRepositorio;
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