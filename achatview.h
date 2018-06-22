#ifndef ACHATVIEW_H
#define ACHATVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>

#include <iostream>

#include "jeu.h"
#include "achats/achat.h"

class MainWindow;

namespace Ui {
class AchatView;
}

class AchatView : public QWidget
{
    Q_OBJECT

public:
    explicit AchatView(QWidget *parent = 0, Jeu* jeu = NULL, Achat* achat = NULL, MainWindow *mainWindow = NULL);
    ~AchatView();

    void updateValues();
    void updateBuyButton(int nb = -1);
    void updateBuyButtonEnable(int nb = -1);
    void updateSellButton(int nb = -1);
    void updateSellButtonEnable(int nb = -1);

    void buy(int i = 1);
    void sell(int i = 1);

private slots:
    void on_pbAchat_clicked();

    void on_pbVente_clicked();

    void on_sbNbBuy_valueChanged(int arg1);

    void on_pbBuyMin_clicked();

    void on_sbNbSell_valueChanged(int arg1);

    void on_pbBuyMax_clicked();

    void on_pbSellMax_clicked();

    void on_pbSellMin_clicked();

private:
    Ui::AchatView *ui;
    Jeu* _jeu;
    Achat* _achat;
    MainWindow* _mainWindow;

    int _maxVentes;
    int _maxAchats;
};

#endif // ACHATVIEW_H
