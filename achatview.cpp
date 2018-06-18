#include "achatview.h"
#include "ui_achatview.h"

#include"mainwindow.h"

AchatView::AchatView(QWidget *parent, Jeu *jeu, Achat *achat, MainWindow *mainWindow) :
    QWidget(parent),
    ui(new Ui::AchatView),
    _jeu(jeu),
    _achat(achat),
    _mainWindow(mainWindow)
{
    ui->setupUi(this);
    updateButtons();
}

AchatView::~AchatView()
{
    delete ui;
}

void AchatView::updateValues()
{
    ui->labelNom->setText("<strong>" + QString::number(_achat->getNb()) + "</strong> " + _achat->nomAffichage());
    ui->labelInfo->setText("<strong>" + QString::number(_achat->getRevenuBaseSecond()) + "</strong> roubles/seconde par unité (<strong>" + QString::number(_achat->getTotalRevenuParMs(1000)) + "</strong> roubles/seconde au total)");

    updateButtons();
}

void AchatView::on_sbNb_valueChanged(int arg1)
{
    updateButtons(arg1);
}

void AchatView::updateButtons(int nb)
{
    if(nb == -1)
    {
        nb = ui->sbNb->value();
    }
    ui->pbAchat->setText("Acheter " + QString::number(nb) + " (" + QString::number(_achat->getPrixNext(nb)) + " roubles)");
    ui->pbVente->setText("Vendre " + QString::number(nb) + " (" + QString::number(_achat->getPrixVenteNext(nb)) + " roubles)");

    updateButtonsEnable(nb);
}

void AchatView::updateButtonsEnable(int nb)
{
    if(nb == -1)
    {
        nb = ui->sbNb->value();
    }

    if(_jeu->getRoubles() >= _achat->getPrixNext(nb)) {
        ui->pbAchat->setEnabled(true);
    }
    else {
        ui->pbAchat->setDisabled(true);
    }

    if(nb > _achat->getNb()) {
        ui->pbVente->setDisabled(true);
    }
    else {
        ui->pbVente->setEnabled(true);
    }
}

void AchatView::on_pbAchat_clicked()
{
    buy(ui->sbNb->value());
    updateValues();
    _mainWindow->updateValues();
}

void AchatView::buy(int i)
{
    double prix = _achat->getPrixNext(i);
    if(prix <= _jeu->getRoubles())
    {
        _jeu->payerRoubles(_achat->getPrixNext(i));
        _achat->buy(i);
        _mainWindow->setStatusText(_achat->texteInfo());
    }
    else
    {
        QMessageBox::critical(_mainWindow,"Achat impossible !", "Vous n'avez pas assez de roubles pour acheter ceci.");
    }
}

void AchatView::sell(int i)
{
    if(i <= _achat->getNb())
    {
        _achat->sell(i);
        _jeu->gagnerRoubles(_achat->getPrixVenteNext(i));
    }
    else
    {
        QMessageBox::critical(_mainWindow,"Vente impossible !", "Vous ne pouvez pas vendre autant d'exemplaires de cet élément.");
    }
}

void AchatView::on_pbVente_clicked()
{
    sell(ui->sbNb->value());
    updateValues();
    _mainWindow->updateValues();
}
