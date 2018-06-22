#ifndef JEU_H
#define JEU_H

#include <QString>
#include <QMessageBox>
#include <vector>
#include <string>
#include <QTimer>
#include <map>

#include "achats/achat.h"
#include "achats/manifeste.h"
#include "achats/petitlivrerouge.h"
#include "achats/typeachat.h"

class MainWindow;

class Jeu
{
public:
    Jeu(MainWindow* fenetre, std::string chemin = "sauvegarde.sav", bool autoSave = true);
    ~Jeu();

    bool autoSave();
    void setAutoSave(bool autoSave);

    bool cheatEnabled();
    void enableCheat();

    void setMainWindow(MainWindow* fenetre);
    void ajouterRoubles();
    void ajouterRoublesClic();
    double getRoublesParMs(int millisecondes);
    double getRoubles();
    double getRoublesParClic();

    void gagnerRoubles(double nbRoubles);
    void payerRoubles(double nbRoubles);
    void setRoubles(double nbRoubles);

    int computeNextDoubleBonusTime();

    Achat* getAchat(TypeAchat::TypeAchat type);
    std::vector<Achat*> getAchats();

    bool sauvegarder(std::string chemin = "sauvegarde.sav");

private:
    const static int SAVE_VERSION = 2;

    MainWindow* _fenetre;

    double _roubles;
    bool _autoSave;
    bool _cheatEnabled;
    QTimer* _nextDoubleBonus;

    // Achats
    std::vector<Achat*> _achats;
};

#endif // JEU_H
