#include "modifierR.h"
#include "ui_modifierR.h"
#include "reclamation.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QString>
#include <QMessageBox>
modifierR::modifierR(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifierR)
{
    ui->setupUi(this);
}

modifierR::~modifierR()
{
    delete ui;
}
bool reclamation::modifier()
{
    QSqlQuery query;
          query.prepare("UPDATE RECLAMATION set CIN=:CIN,NomC=:NomC,PrenomC=:PrenomC,DescriptionR=:DescriptionR where IDR=:IDR");
          query.bindValue(":CIN",CIN);
          query.bindValue(":IDR",IDR);
          query.bindValue(":NomC",NomC);
          query.bindValue(":PrenomC",PrenomC);
          query.bindValue(":DescriptionR",DescriptionR);

          return query.exec();
}


void modifierR::on_pb_modifier_clicked()
{
    QSqlQueryModel *modal=new QSqlQueryModel;
        QSqlQuery *qry=new QSqlQuery;
        qry->prepare("select IDR from RECLAMATION");
        qry->exec();
        modal->setQuery(*qry);
        int IDR=ui->le_IDR_2->text().toInt();
        QString NomC=ui->le_nom_2->text();
        QString PrenomC=ui->le_prenom_2->text();
        int CIN=ui->le_CIN_2->text().toInt();

        QString DescriptionR=ui->le_Description_2->text();
         reclamation R2(CIN,NomC,PrenomC,IDR,DescriptionR);
         bool test=R2.modifier();
         if(test)
         {
             QMessageBox::information(nullptr, QObject::tr("update is ok"),
                         QObject::tr(" successful.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

         }
         else
             QMessageBox::critical(nullptr, QObject::tr("update not ok"),
                         QObject::tr(" failed.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
}
