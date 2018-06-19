#ifndef JEU_H
#define JEU_H

#include <QString>
#include <QMessageBox>
#include <vector>
#include <string>
#include <map>

#include "achats/achat.h"
#include "achats/manifeste.h"
#include "achats/petitlivrerouge.h"
#include "achats/typeachat.h"

class MainWindow;

class Jeu
{
public:
    Jeu(MainWindow* fenetre, std::string chemin = "sauvegarde.sav");

    bool autoSave();
    void setAutoSave(bool autoSave);

    void setMainWindow(MainWindow* fenetre);
    void ajouterRoubles();
    void ajouterRoublesClic();
    double getRoublesParMs(int millisecondes);
    double getRoubles();
    double getRoublesParClic();

    void gagnerRoubles(double nbRoubles);
    void payerRoubles(double nbRoubles);

    Achat* getAchat(TypeAchat::TypeAchat type);
    std::vector<Achat*> getAchats();

    void sauvegarder(std::string chemin = "sauvegarde.sav");

private:
    MainWindow* _fenetre;
    double _roubles;

    bool _autoSave;

    // Achats
    std::vector<Achat*> _achats;
};

#endif // JEU_H
