#include "jeu.h"
#include "mainwindow.h"

Jeu::Jeu(MainWindow* fenetre) :
    _fenetre(fenetre),
    _roubles(0)
{
    _manifeste = new Manifeste();
    _achats.push_back(_manifeste);
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
    return _manifeste->getTotalRevenuParMs(millisecondes);
}

double Jeu::getRoubles()
{
    return _roubles;
}

double Jeu::getRoublesParClic()
{
    return 1;
}

void Jeu::sauvegarder(QString chemin)
{
    std::ofstream sauvegarde(chemin.toStdString(), std::ios::out | std::ios::binary);

    if(sauvegarde.is_open())
    {
        sauvegarde.write((char*)this, sizeof(Jeu));
    }
    else
    {
        QMessageBox::critical(_fenetre,"Sauvegarde impossible","Le fichier de sauvegarde ne peut être écrit. Vérifiez que vous avez les droits d'écriture dessus.");
    }
}

Achat* Jeu::getAchat(TypeAchat type)
{
    Achat* retour = NULL;
    switch(type) {
    case ManifesteParti:
        retour = _manifeste;
        break;
//        std::cout << _manifeste->getPrixDeBase() << std::endl;
    }

    return retour;
}

void Jeu::gagnerRoubles(double nbRoubles)
{
    _roubles += nbRoubles;
    _fenetre->changeRoubles();
}

void Jeu::payerRoubles(double nbRoubles)
{
    _roubles -= nbRoubles;
    _fenetre->changeRoubles();
}
