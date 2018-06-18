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
    changeRoublesParSeconde();
    changeRoublesParClic();
}

void MainWindow::changeRoubles()
{
    ui->labelRoubles->setText(QString::number(jeu->getRoubles()) + " roubles");
}

void MainWindow::changeRoublesParSeconde()
{
    ui->labelRoublesParSeconde->setText(QString::number(jeu->getRoublesParMs(1000)) + " roubles/seconde");
}

void MainWindow::changeRoublesParClic()
{
    ui->labelRoublesParClic->setText(QString::number(jeu->getRoublesParClic()) + " roubles/clic");
}

void MainWindow::on_boutonTravailler_pressed()
{
    jeu->ajouterRoublesClic();
}
