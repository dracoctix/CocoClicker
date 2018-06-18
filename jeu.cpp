#include "jeu.h"

Jeu::Jeu(MainWindow* fenetre) :
    _fenetre(fenetre),
    _roubles(0)
{

}

void Jeu::setMainWindow(MainWindow *fenetre)
{
    _fenetre = fenetre;
}

void Jeu::ajouterRoubles()
{
    _roubles += getRoublesParMs(10);
}

double Jeu::getRoublesParMs(int millisecondes)
{
    return millisecondes;
}
