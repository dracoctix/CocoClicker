#include "jeu.h"
#include "mainwindow.h"

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
    _fenetre->changeRoubles();
}

void Jeu::ajouterRoublesClic()
{
    _roubles += getRoublesParClic();
    _fenetre->changeRoubles();
}

double Jeu::getRoublesParMs(int millisecondes)
{
    return millisecondes;
}

double Jeu::getRoubles()
{
    return _roubles;
}

double Jeu::getRoublesParClic()
{
    return 1;
}
