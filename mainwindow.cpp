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

void MainWindow::removeAchatsViews()
{
    for (auto widget: ui->tabAchats->children()) {
      delete widget;
    }

    _vuesAchat.clear();
}

void MainWindow::addAchatsViews()
{
    QVBoxLayout* layout = new QVBoxLayout(ui->tabAchats);
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

void MainWindow::on_actionR_initialiser_triggered()
{
    bool firstConfirm, secondConfirm;
    firstConfirm = (QMessageBox::information(this,"Confirmation","Êtes-vous sûr de vouloir recommencer ? Tous vos roubles, achats et améliorations seront perdus.",QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No) == QMessageBox::StandardButton::Yes);
    if(!firstConfirm) return;
    secondConfirm = (!jeu->autoSave() || (QMessageBox::warning(this,"Confirmation", "Attention. La sauvegarde automatique est activée. Si vous continuez, il vous sera impossible de récupérer votre progression. Êtes-vous sûr de vouloir poursuivre ?", QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No) == QMessageBox::StandardButton::Yes));
    if(secondConfirm) {
        reset();
        setStatusText("Le gouvernement soviétique s'est effondré, et vos efforts sont réduits à néant.");
    }
}

bool MainWindow::deleteSave(std::string chemin)
{
    int resultat = std::remove(chemin.c_str());
    if(resultat != 0)
    {
        QMessageBox::critical(this,"La sauvegarde ne peut être supprimée.", "La suppression de la sauvegarde a échoué.<br>(code d'erreur : " + QString::number(resultat,16) + ")");
        return false;
    }

    return true;
}

void MainWindow::reset(std::string chemin)
{
    bool autoSave = jeu->autoSave();
    removeAchatsViews();

    delete(jeu);
    jeu = new Jeu(this,chemin,autoSave);
    addAchatsViews();
}

void MainWindow::on_actionSupprimer_la_sauvegarde_triggered()
{
    if(QMessageBox::information(this,"Confirmation","Etes-vous sûr de vouloir supprimer votre sauvegarde ? Cette action est irréversible.",QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        if(deleteSave())
        {
            setStatusText("Les archives socialistes ont été détruites.");
        }
    }
}

void MainWindow::on_actionRevenir_la_derni_re_sauvegarde_triggered()
{
    if(QMessageBox::information(this,"Confirmation","Êtes-vous sûr de vouloir revenir à la dernière sauvegarde ? Tous vos gains acquis depuis la dernière sauvegarde seront effacés.",QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        reset("sauvegarde.sav");
        setStatusText("Vous avez récupéré les archives du parti.");
    }
}

void MainWindow::on_actionExporter_sauvegarde_triggered()
{
    QString chemin = QFileDialog::getSaveFileName(this,"Exporter la sauvegarde...",QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), "Fichier de sauvegarde Coco Clicker (*.cocosave)");
    if(chemin != NULL)
    {
        if(jeu->sauvegarder(chemin.toStdString()))
        {
            setStatusText("Les archives du parti ont été mises en sécurité.");
        }
    }
}

void MainWindow::on_actionLire_sauvegarde_triggered()
{
    QString chemin = QFileDialog::getOpenFileName(this,"Lire la sauvegarde...", QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0],"Fichier de sauvegarde Coco Clicker (*.cocosave)");
    if(chemin != NULL)
    {
        reset(chemin.toStdString());
        setStatusTip("Les archives ont été récupérées.");
    }
}
