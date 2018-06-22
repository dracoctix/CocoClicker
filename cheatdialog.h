#ifndef CHEATDIALOG_H
#define CHEATDIALOG_H

#include <QDialog>
#include <QDoubleSpinBox>
#include <QGroupBox>

#include "jeu.h"

namespace Ui {
class CheatDialog;
}

class CheatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CheatDialog(QWidget *parent = 0, Jeu *jeu = 0);
    ~CheatDialog();

    double getRoubles();
    bool bonus();
    double bonusTime();

private:
    Ui::CheatDialog *ui;
    Jeu* _jeu;
};

#endif // CHEATDIALOG_H
