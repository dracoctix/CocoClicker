#ifndef JEU_H
#define JEU_H

#include <QString>
#include <QMessageBox>

#include "achats/achat.h"
#include "achats/manifeste.h"
#include "achats/typeachat.h"

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

    void gagnerRoubles(double nbRoubles);
    void payerRoubles(double nbRoubles);

    Achat* getAchat(TypeAchat type);

    void sauvegarder(QString chemin);

private:
    MainWindow* _fenetre;
    double _roubles;

    // Achats
    Manifeste* _manifeste;
};

#endif // JEU_H
