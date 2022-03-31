#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bien.h"
#include "supprimerR.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bien B;
ui->bien->setModel(B.afficher());
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_Ajouter_clicked()
{
   int id_imo=ui->le_id->text().toInt();
int id_imo=ui->
QString typeC=ui->le_type->text();
QString dateC=ui->le_date->text();
int prix=ui->le_prix->text().toInt();
QString DescriptionB=ui->le_Description->text();
    bien b(id_imo,typeC,dateC,prix,DescriptionB);
    bool test=B.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("add is ok"),
                    QObject::tr(" successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("add not ok"),
                    QObject::tr(" failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    bien B;
    ui->bien->setModel(B.afficher());
}

void MainWindow::on_Supprimer_clicked()
{
  supprimerR supprimerr;
  supprimerr.setModal(true);
  supprimerr.exec();
}
