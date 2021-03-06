#ifndef ACHAT_H
#define ACHAT_H

#include <QString>

#include <iostream>
#include <cmath>

#include "typeachat.h"

class Achat
{
public:
    Achat();
    ~Achat();

    int getNb();
    void buy(int nb = 1);
    void sell(int nb = 1);
    void setNb(int nb = 0);

    virtual double getPrixDeBase() =0;
    double getPrixNext(int nb = 1);
    double getPrixLevel(int level = 1);

    double getPrixVenteNext(int nb = 1);
    double getPrixVenteLevel(int level = 1);

    void enable();
    void disable();

    double getRevenuParMs(int milliseconds = 1000);
    double getTotalRevenuParMs(int milliseconds = 1000);
    virtual double getRevenuBaseSecond() =0;
    double getRapportLevel();

    virtual QString nomAffichage() =0;

    virtual QString texteInfo() =0;

    virtual TypeAchat::TypeAchat typeAchat() =0;

    int getBuyableLevels(double roubles);

private:
    int _nb;
    bool _enabled;
};

#endif // ACHAT_H
