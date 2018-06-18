#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    jeu = new Jeu(this);

    std::ifstream sauvegarde("sauvegarde.sav",std::ios::in | std::ios::binary);
    if(sauvegarde.is_open())
    {
        sauvegarde.read((char*)jeu, sizeof(Jeu));
        jeu->setMainWindow(this);
    }

    _timer.start(10);

    QObject::connect(&_timer,SIGNAL(timeout()), this, SLOT(ajouterRoubles()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSauvegarde_rapide_triggered()
{
    std::ofstream sauvegarde("sauvegarde.sav", std::ios::out | std::ios::binary);

    if(sauvegarde.is_open())
    {
        sauvegarde.write((char*)jeu, sizeof(Jeu));
    }
    else
    {
        QMessageBox::critical(this,"Sauvegarde impossible","Le fichier de sauvegarde ne peut être écrit. Vérifiez que vous avez les droits d'écriture dessus.");
    }
}

void MainWindow::ajouterRoubles()
{
    jeu->ajouterRoubles();
}

void MainWindow::changeRoubles()
{
    // TODO : Afficher le changement de roubles.
    return;
}
