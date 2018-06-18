#ifndef JEU_H
#define JEU_H

#include <QMainWindow>

class MainWindow;

class Jeu
{
public:
    Jeu(MainWindow* fenetre);

    void setMainWindow(MainWindow* fenetre);
    void ajouterRoubles();
    double getRoublesParMs(int millisecondes);

private:
    MainWindow* _fenetre;
    double _roubles;
};

#endif // JEU_H
