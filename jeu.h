#ifndef JEU_H
#define JEU_H

#include <QMainWindow>

//#include "mainwindow.h"

class MainWindow;

class Jeu
{
public:
    Jeu(MainWindow* fenetre);

    void setMainWindow(MainWindow* fenetre);
    void ajouterRoubles();
    void ajouterRoublesClic();
    double getRoublesParMs(int millisecondes);
    double getRoubles();
    double getRoublesParClic();

private:
    MainWindow* _fenetre;
    double _roubles;
};

#endif // JEU_H
