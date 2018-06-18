#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QLabel>
#include <QList>
#include <QStatusBar>

#include <iostream>
#include <fstream>

#include "jeu.h"
#include "achatview.h"
#include "achats/typeachat.h"

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

public slots:
    void ajouterRoubles();

private slots:
    void on_actionSauvegarde_rapide_triggered();

    void on_boutonTravailler_pressed();

private:
    Ui::MainWindow *ui;
    Jeu *jeu;

    QTimer _timer;

    QList<AchatView*> _vuesAchat;
};

#endif // MAINWINDOW_H
