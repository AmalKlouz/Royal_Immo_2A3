#include "mainwindowins.h"
#include "acceuil.h"
#include "ui_mainwindowins.h"
#include "menu.h"
#include "dialoguser.h"
#include "dialogbien.h"
#include "ui_dialogbien.h"
#include"mapwindow.h"
#include "bien.h"
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
if(tmpu.connecter(ui->EMAIL->text(),ui->MDP->text()))
   { close();
    Menu a;
       a.exec();
      }
else   QMessageBox::critical(nullptr,QObject::tr("LOGIN"),
                             QObject::tr("Verifiez vos donnés"),QMessageBox::Ok);
}


void MainWindowIns::on_commandLinkButton_clicked()
{
     DialogUser d;
    d.exec();
}
