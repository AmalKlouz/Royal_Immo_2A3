#include "menu.h"
#include "ui_menu.h"
#include "dialogclient.h"
#include "dialogbien.h"
#include "acceuil.h"
#include "dialogreclamation.h"
#include "equipmentdialog.h"
Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButton_3_clicked()
{
    DialogClient dc;
    dc.exec();

}

void Menu::on_pushButton_clicked()
{
    acceuil a;
    a.exec();
}

void Menu::on_rec_clicked()
{
    secdialog =new dialogreclamation(this);
    secdialog->show();
}

void Menu::on_bien_m_clicked()
{
    bienndialog =new dialogbien(this);
    bienndialog->show();
}

void Menu::on_equipement_clicked()
{
    equipementDialog =new EquipmentDialog(this);
    equipementDialog->show();
}
