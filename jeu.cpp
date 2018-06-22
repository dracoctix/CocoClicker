#include "jeu.h"
#include "mainwindow.h"

Jeu::Jeu(MainWindow* fenetre, std::string chemin, bool autoSave) :
    _fenetre(fenetre),
    _roubles(0),
    _autoSave(autoSave),
    _cheatEnabled(false),
    _activeBonus(false)
{
    Manifeste* manifeste = new Manifeste();
    _achats.push_back(manifeste);

    PetitLivreRouge* petitLivreRouge = new PetitLivreRouge();
    _achats.push_back(petitLivreRouge);

    _nextDoubleBonus = new QTimer(_fenetre);
    _timeBeforeBonusEnd = new QTimer(_fenetre);

    int nextTimer = computeNextDoubleBonusTime();

    std::ifstream sauvegarde;
    if(!chemin.empty())
    {
        sauvegarde = std::ifstream(chemin, std::ios::in | std::ios::binary);
    }

    if(sauvegarde.is_open()) {
        int version;

        sauvegarde.read((char*)&version, sizeof(int));

        if(version == SAVE_VERSION) {
            sauvegarde.read((char*)&_roubles, sizeof(double));
            sauvegarde.read((char*)&_autoSave, sizeof(bool));
            sauvegarde.read((char*)&_cheatEnabled, sizeof(bool));
            sauvegarde.read((char*)&_activeBonus, sizeof(bool));
            sauvegarde.read((char*)&nextTimer, sizeof(int));

            for(Achat* achat : _achats)
            {
                TypeAchat::TypeAchat typeAchat;
                int nb;
                sauvegarde.read((char*)&typeAchat, sizeof(TypeAchat::TypeAchat));
                sauvegarde.read((char*)&nb, sizeof(int));

                getAchat(typeAchat)->setNb(nb);
            }
        }
        else {
            QMessageBox::critical(fenetre,"Sauvegarde incompatible.","La sauvegarde que vous tentez de charger correspond à une version du jeu utilisant un format de sauvegarde différent. La sauvegarde n'a donc pas pu être chargée.<br>(Version de la sauvegarde : <strong>" + QString::number(version) + "</strong>, version du jeu : <strong>" + QString::number(SAVE_VERSION) + "</strong>)");
        }
    }

    if(!_activeBonus) {
        _nextDoubleBonus->start(nextTimer);
    }
    else {
        _timeBeforeBonusEnd->start(nextTimer);
    }

    QObject::connect(_nextDoubleBonus,SIGNAL(timeout()),_fenetre,SLOT(newBonusButton()));
    QObject::connect(_timeBeforeBonusEnd,SIGNAL(timeout()),_fenetre, SLOT(endBonus()));
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

void Jeu::enableCheat()
{
    _cheatEnabled = true;
}

bool Jeu::cheatEnabled()
{
    return _cheatEnabled;
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

    int bonus = _activeBonus ? 2 : 1;

    return bonus*gain;
}

double Jeu::getRoubles()
{
    return _roubles;
}

double Jeu::getRoublesParClic()
{
    int bonus = _activeBonus ? 2 : 1;
    return 1*bonus;
}

bool Jeu::sauvegarder(std::string chemin)
{
    bool retour = false;
    std::ofstream sauvegarde(chemin, std::ios::out | std::ios::binary);

    if(sauvegarde.is_open())
    {
        int version = SAVE_VERSION;
        sauvegarde.write((char*)&version, sizeof(int));

        sauvegarde.write((char*)&_roubles, sizeof(double));
        sauvegarde.write((char*)&_autoSave, sizeof(bool));
        sauvegarde.write((char*)&_cheatEnabled, sizeof(bool));
        sauvegarde.write((char*)&_activeBonus, sizeof(bool));
        int remainingTime;
        if(_activeBonus) {
            remainingTime = _timeBeforeBonusEnd->remainingTime();
        }
        else {
            remainingTime = _nextDoubleBonus->remainingTime();
        }

        // On sauvegarde le temps restant avant le prochain événement quel qu'il soit.
        sauvegarde.write((char*)&remainingTime, sizeof(int));

        for(Achat* achat : _achats)
        {
            int nb = achat->getNb();
            TypeAchat::TypeAchat typeAchat = achat->typeAchat();
            sauvegarde.write((char*)&typeAchat, sizeof(TypeAchat::TypeAchat));
            sauvegarde.write((char*)&nb, sizeof(int));
        }

        retour = true;
    }
    else
    {
        QMessageBox::critical(_fenetre,"Sauvegarde impossible","Le fichier de sauvegarde ne peut être écrit. Vérifiez que vous avez les droits d'écriture dessus.");
        retour = false;
    }

    return retour;
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

void Jeu::setRoubles(double nbRoubles)
{
    _roubles = nbRoubles;
    _fenetre->changeRoubles();
}

int Jeu::computeNextDoubleBonusTime()
{
    return ((rand() % 25)+5) * 30 * 1000;
}

std::vector<Achat*> Jeu::getAchats()
{
    return _achats;
}

void Jeu::resetTimer()
{
    _nextDoubleBonus->start(computeNextDoubleBonusTime());
}

bool Jeu::isActiveBonus()
{
    return _activeBonus;
}

void Jeu::setActiveBonus(bool activeBonus)
{
    if(activeBonus)
        _timeBeforeBonusEnd->start(30000);
    _activeBonus = activeBonus;
}

int Jeu::getRemainingBonusTime()
{
    return _timeBeforeBonusEnd->remainingTime()/1000;
}

void Jeu::forceBonusSpawn()
{

}
