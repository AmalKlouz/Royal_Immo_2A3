#include "supprimerR.h"
#include "ui_supprimerR.h"
#include "reclamation.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QString>
#include <QMessageBox>

supprimerR::supprimerR(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::supprimerR)
{
    ui->setupUi(this);
}

supprimerR::~supprimerR()
{
    delete ui;
}
bool reclamation::supprimer(int IDR)
{
    QSqlQuery query;
     query.prepare("Delete from RECLAMATION where IDR=:IDR");
     query.bindValue(0, IDR);

     return  query.exec();

}
void supprimerR::on_pb_supprimer_clicked()
{
reclamation R1; R1.setIDR(ui->le_id_supp->text().toInt());
bool test=R1.supprimer(R1.getIDR());
if(test)
{
    QMessageBox::information(nullptr, QObject::tr("delete is ok"),
                QObject::tr(" successful.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("delete not ok"),
                QObject::tr(" failed.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
