#include "mainwindowins.h"
#include "acceuil.h"
#include "ui_mainwindowins.h"

MainWindowIns::MainWindowIns(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowIns)
{
    ui->setupUi(this);
}

MainWindowIns::~MainWindowIns()
{
    delete ui;
}

void MainWindowIns::on_pushButton_clicked()
{
if(tmpe.connecter(ui->ID->text().toInt(),ui->MDP->text()))
   { close();
    acceuil a;
       a.exec();
      }
else   QMessageBox::critical(nullptr,QObject::tr("LOGIN"),
                             QObject::tr("Verifiez vos donnés"),QMessageBox::Ok);
}

