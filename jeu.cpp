#include "jeu.h"
#include "mainwindow.h"

Jeu::Jeu(MainWindow* fenetre) :
    _fenetre(fenetre),
    _roubles(0)
{
    _manifeste = new Manifeste();
    _achats.push_back(_manifeste);

    _petitLivreRouge = new PetitLivreRouge();
    _achats.push_back(_petitLivreRouge);
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
    double gain = 0;
    for(Achat* achat : _achats) {
        gain += achat->getTotalRevenuParMs(millisecondes);
    }
    return gain;
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

Achat* Jeu::getAchat(TypeAchat::TypeAchat type)
{
    Achat* retour = NULL;
    switch(type) {
    case TypeAchat::ManifesteParti:
        retour = _manifeste;
        break;

    case TypeAchat::PetitLivreRouge:
        retour = _petitLivreRouge;
        break;
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

std::vector<Achat*> Jeu::getAchats()
{
    return _achats;
}
