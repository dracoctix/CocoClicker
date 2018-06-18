#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>

#include <iostream>
#include <fstream>

#include "jeu.h"

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

public slots:
    void ajouterRoubles();

private slots:
    void on_actionSauvegarde_rapide_triggered();

private:
    Ui::MainWindow *ui;
    Jeu *jeu;

    QTimer _timer;
};

#endif // MAINWINDOW_H
