#include "cheatdialog.h"
#include "ui_cheatdialog.h"

CheatDialog::CheatDialog(QWidget *parent, Jeu *jeu) :
    QDialog(parent),
    ui(new Ui::CheatDialog),
    _jeu(jeu)
{
    ui->setupUi(this);
    ui->sbRoubles->setValue(jeu->getRoubles());
    ui->gbBonus->setChecked(jeu->isActiveBonus());
    if(jeu->isActiveBonus())
        ui->sbBonusTime->setValue(jeu->getRemainingBonusTime());
}

CheatDialog::~CheatDialog()
{
    delete ui;
}

double CheatDialog::getRoubles()
{
    return ui->sbRoubles->value();
}

bool CheatDialog::bonus()
{
    return ui->gbBonus->isChecked();
}

double CheatDialog::bonusTime()
{
    return ui->sbBonusTime->value() * 1000;
}

void CheatDialog::on_pbSpawnBonus_clicked()
{
    _jeu->forceBonusSpawn();
}
