#include "jeu.h"
#include "mainwindow.h"

Jeu::Jeu(MainWindow* fenetre, std::string chemin, bool autoSave) :
    _fenetre(fenetre)
{
    std::ifstream sauvegarde;
    if(!chemin.empty())
    {
        sauvegarde = std::ifstream(chemin, std::ios::in | std::ios::binary);
    }

    Manifeste* manifeste = new Manifeste();
    _achats.push_back(manifeste);

    PetitLivreRouge* petitLivreRouge = new PetitLivreRouge();
    _achats.push_back(petitLivreRouge);

    _roubles = 0;
    _autoSave = autoSave;

    if(sauvegarde.is_open()) {

        sauvegarde.read((char*)&_roubles, sizeof(double));
        sauvegarde.read((char*)&_autoSave, sizeof(bool));

        for(Achat* achat : _achats)
        {
            TypeAchat::TypeAchat typeAchat;
            int nb;
            sauvegarde.read((char*)&typeAchat, sizeof(TypeAchat::TypeAchat));
            sauvegarde.read((char*)&nb, sizeof(int));

            getAchat(typeAchat)->setNb(nb);
        }
    }
}

Jeu::~Jeu()
{
    for(auto* achat : _achats) {
        delete(achat);
    }
}

void Jeu::setAutoSave(bool autoSave)
{
    _autoSave = autoSave;
}

bool Jeu::autoSave()
{
    return _autoSave;
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

void Jeu::sauvegarder(std::string chemin)
{
    std::ofstream sauvegarde(chemin, std::ios::out | std::ios::binary);

    if(sauvegarde.is_open())
    {
//        std::map<TypeAchat::TypeAchat, int> nombres;
//        std::map<TypeAchat::TypeAchat, int>::iterator it;

//        for(it = nombres.begin(); it != nombres.end(); ++it)
//        {

//        }

        sauvegarde.write((char*)&_roubles, sizeof(double));
        sauvegarde.write((char*)&_autoSave, sizeof(bool));
        for(Achat* achat : _achats)
        {
            int nb = achat->getNb();
            TypeAchat::TypeAchat typeAchat = achat->typeAchat();
            sauvegarde.write((char*)&typeAchat, sizeof(TypeAchat::TypeAchat));
            sauvegarde.write((char*)&nb, sizeof(int));
        }
    }
    else
    {
        QMessageBox::critical(_fenetre,"Sauvegarde impossible","Le fichier de sauvegarde ne peut être écrit. Vérifiez que vous avez les droits d'écriture dessus.");
    }
}

Achat* Jeu::getAchat(TypeAchat::TypeAchat type)
{
    Achat* retour = NULL;
    for(Achat* achat : _achats) {
        if(achat->typeAchat() == type) {
            retour = achat;
        }
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
