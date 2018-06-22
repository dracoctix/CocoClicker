#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QLabel>
#include <QList>
#include <QStatusBar>
#include <QLayout>
#include <QAction>
#include <QFileDialog>
#include <QStandardPaths>

#include <iostream>
#include <fstream>
#include <cstdio>

#include "jeu.h"
#include "achatview.h"
#include "achats/typeachat.h"
#include "cheatdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void changeRoubles();
    void changeRoublesParSeconde();
    void changeRoublesParClic();

    void updateValues();

    void setStatusText(QString texte);

    void removeAchatsViews();
    void addAchatsViews();

    bool deleteSave(std::string chemin = "sauvegarde.sav");
    void reset(std::string chemin = "");

    Jeu* getJeu();

public slots:
    void ajouterRoubles();
    void newBonusButton();
    void timeoutBonusButton();
    void startBonus();
    void endBonus();

private slots:
    void on_actionSauvegarde_rapide_triggered();

    void on_boutonTravailler_pressed();

    void on_actionSauvegarde_automatique_triggered(bool checked);

    void on_actionR_initialiser_triggered();

    void on_actionSupprimer_la_sauvegarde_triggered();

    void on_actionRevenir_la_derni_re_sauvegarde_triggered();

    void on_actionExporter_sauvegarde_triggered();

    void on_actionLire_sauvegarde_triggered();

    void on_actionTricher_triggered();

private:
    Ui::MainWindow *ui;
    Jeu *jeu;

    QTimer _timer;

    QList<AchatView*> _vuesAchat;

    QPushButton* _bonusButton;
};

#endif // MAINWINDOW_H
