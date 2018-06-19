#include "manifeste.h"

Manifeste::Manifeste()
{
}

double Manifeste::getRevenuBaseSecond()
{
    return 1;
}

double Manifeste::getPrixDeBase()
{
    return 50;
}

QString Manifeste::nomAffichage()
{
    return "Manifeste du parti communiste";
}

QString Manifeste::texteInfo()
{
    return "La pensée de Karl Marx a été propagée.";
}

TypeAchat::TypeAchat Manifeste::typeAchat()
{
    return TypeAchat::ManifesteParti;
}
