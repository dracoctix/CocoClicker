#include "petitlivrerouge.h"

PetitLivreRouge::PetitLivreRouge()
{

}

double PetitLivreRouge::getRevenuBaseSecond()
{
    return 5;
}

double PetitLivreRouge::getPrixDeBase()
{
    return 500;
}

QString PetitLivreRouge::nomAffichage()
{
    return "Petit livre rouge";
}

QString PetitLivreRouge::texteInfo()
{
    return "Le peuple a de la lecture et se motive à travailler.";
}

TypeAchat::TypeAchat PetitLivreRouge::typeAchat()
{
    return TypeAchat::PetitLivreRouge;
}
