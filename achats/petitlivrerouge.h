#ifndef PETITLIVREROUGE_H
#define PETITLIVREROUGE_H

#include <QString>

#include "achat.h"

class PetitLivreRouge : public Achat
{
public:
    PetitLivreRouge();

    double getPrixDeBase();
    double getRevenuBaseSecond();
    QString nomAffichage();
    QString texteInfo();

    TypeAchat::TypeAchat typeAchat();
};

#endif // PETITLIVREROUGE_H
