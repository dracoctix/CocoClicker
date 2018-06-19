#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    jeu = new Jeu(this, "sauvegarde.sav");

    ui->actionSauvegarde_automatique->setChecked(jeu->autoSave());

    _timer.start(10);

    QObject::connect(&_timer,SIGNAL(timeout()), this, SLOT(ajouterRoubles()));

//    std::cout << jeu->getAchat(ManifesteParti)->getPrixDeBase() << std::endl;

    addAchatsViews();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSauvegarde_rapide_triggered()
{
    jeu->sauvegarder("sauvegarde.sav");
}

void MainWindow::ajouterRoubles()
{
    jeu->ajouterRoubles();
    updateValues();
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
    updateValues();
    setStatusText("Vous avez collecté " + QString::number(jeu->getRoublesParClic()) + " roubles en travaillant pour construire un canal.");
}

void MainWindow::updateValues()
{
    changeRoubles();
    changeRoublesParClic();
    changeRoublesParSeconde();

    for(AchatView* widget : _vuesAchat) {
        widget->updateValues();
    }

    if(jeu->autoSave()) {
        jeu->sauvegarder("sauvegarde.sav");
    }
}

void MainWindow::setStatusText(QString texte)
{
    ui->statusBar->showMessage(texte);
}

void MainWindow::addAchatsViews()
{
    QVBoxLayout* layout = new QVBoxLayout(ui->tabAchats);
    ui->tabAchats->setLayout(layout);
    AchatView* achatView;
    for(Achat* a : jeu->getAchats())
    {
        achatView = new AchatView(ui->tabAchats, jeu, a, this);
        layout->addWidget(achatView);
        _vuesAchat.append(achatView);
        ui->tabAchats->setMinimumWidth(achatView->width());
    }
}

void MainWindow::on_actionSauvegarde_automatique_triggered(bool checked)
{
    jeu->setAutoSave(checked);
}
