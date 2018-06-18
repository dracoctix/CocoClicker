#ifndef MANIFESTE_H
#define MANIFESTE_H

#include "achat.h"

class Manifeste : public Achat
{
public:
    Manifeste();

    double getRevenuBaseSecond();
    double getPrixDeBase();
    QString nomAffichage();
    QString texteInfo();
};

#endif // MANIFESTE_H
