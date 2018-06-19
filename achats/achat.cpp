#include "achat.h"

Achat::Achat() :
    _nb(0),
    _enabled(false)
{

}

Achat::~Achat()
{
    std::cout << "Destruction !"  << std::endl;
}

int Achat::getNb()
{
    return _nb;
}

void Achat::buy(int nb)
{
    _nb += nb;
}

void Achat::sell(int nb)
{
    _nb -= nb;
}

void Achat::setNb(int nb)
{
    _nb = nb;
}

double Achat::getPrixNext(int nb)
{
    double prixNext = 0;
    for(int i = _nb+1 ; i <= _nb+nb; ++i) {
        prixNext += getPrixLevel(i);
    }
    return prixNext;
}

double Achat::getPrixLevel(int level)
{
    double prix = getPrixDeBase();

    for(int i = 2; i <= level; ++i)
    {
        prix *= 1.025;
    }

    return prix;
}

void Achat::enable()
{
    _enabled = true;
}

void Achat::disable()
{
    _enabled = false;
}

double Achat::getRevenuParMs(int milliseconds)
{
    return 0.001*milliseconds*getRevenuBaseSecond();
}

double Achat::getTotalRevenuParMs(int milliseconds)
{
    return getRevenuParMs(milliseconds) * _nb;
}

double Achat::getPrixVenteLevel(int level)
{
    return getPrixLevel(level) / 2.0;
}

double Achat::getPrixVenteNext(int nb)
{
    double prix = 0;

    for(int i = nb; i > 0; --i) {
        prix += getPrixVenteLevel(i);
    }

    return prix;
}
