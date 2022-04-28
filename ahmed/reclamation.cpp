#include "reclamation.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
reclamation::reclamation()
{
CIN=0;IDR=0;
}

reclamation::reclamation(int CIN,QString NomC,QString PrenomC,int IDR,QString DescriptionR)
{
    this->CIN=CIN;this->NomC=NomC;this->PrenomC=PrenomC;this->IDR=IDR;this->DescriptionR=DescriptionR;
}

int reclamation::getCIN(){return CIN;}

QString reclamation::getNomC(){return NomC;}
QString reclamation::getPrenomC(){return PrenomC;}
int reclamation::getIDR(){return IDR;}
QString reclamation::getDescriptionR(){return DescriptionR;}
void reclamation::setCIN(int CIN){this->CIN=CIN;}

void reclamation::setNomC(QString NomC){this->NomC=NomC;}
void reclamation::setPrenomC(QString PrenomC){this->PrenomC=PrenomC;}
void reclamation::setIDR(int IDR){this->IDR=IDR;}
void reclamation::setDescriptionR(QString DescriptionR){this->DescriptionR=DescriptionR;}
bool reclamation::ajouter()
{
    QString CIN_string=QString::number(CIN);
    QString idr_string=QString::number(IDR);
        QSqlQuery query;

         query.prepare("INSERT INTO RECLAMATION (CIN,IDR, NomC ,PrenomC ,DescriptionR) "
                       "VALUES (:CIN ,:IDR, :NomC, :PrenomC, :DescriptionR)");
         query.bindValue(0, CIN_string);
         query.bindValue(2, NomC);
         query.bindValue(3, PrenomC);
         query.bindValue(1, idr_string);
         query.bindValue(4, DescriptionR);
         return  query.exec();
    }
QSqlQueryModel* reclamation::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel;
          model->setQuery("SELECT * FROM RECLAMATION");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDR"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("NomC"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("PrenomC"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DescriptionR"));

    return model;
}
bool reclamation::supprimer(int IDR)
{
    QSqlQuery query;
     query.prepare("Delete from RECLAMATION where IDR=:IDR");
     query.bindValue(0, IDR);

     return  query.exec();

}
bool reclamation::modifier()
{
    if (IDR ==0)
    {
        QMessageBox::critical(nullptr, QObject::tr("chaine vide!"),
                    QObject::tr("ID reclamation obligatoire"), QMessageBox::Cancel);

        return  false;
    }

    if (NomC =="")

    {
        QMessageBox::critical(nullptr, QObject::tr("chaine vide!"),
                    QObject::tr("le nom est vide"), QMessageBox::Cancel);

        return  false;
    }
    if (PrenomC =="")
    {
        QMessageBox::critical(nullptr, QObject::tr("chaine vide!"),
                    QObject::tr("le prenom est vide"), QMessageBox::Cancel);

        return  false;
    }

    if (CIN ==0)
    {
        QMessageBox::critical(nullptr, QObject::tr("chaine vide!"),
                    QObject::tr("CIN est vide"), QMessageBox::Cancel);

        return  false;
    }

    if (DescriptionR =="")
    {
        QMessageBox::critical(nullptr, QObject::tr("chaine vide!"),
                    QObject::tr("la Description est vide"), QMessageBox::Cancel);

        return  false;
    }
    QSqlQuery query;

          query.prepare("UPDATE RECLAMATION set CIN=:CIN,NomC=:NomC,PrenomC=:PrenomC,DescriptionR=:DescriptionR where IDR=:IDR");
          query.bindValue(":CIN",CIN);
          query.bindValue(":IDR",IDR);
          query.bindValue(":NomC",NomC);
          query.bindValue(":PrenomC",PrenomC);
          query.bindValue(":DescriptionR",DescriptionR);

          return query.exec();
}
QSqlQueryModel *reclamation::rechercher(QString rech)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM RECLAMATION WHERE NomC LIKE'%"+rech+"%' or CIN LIKE'%"+rech+"%' or IDR LIKE'%"+rech+"%' or PrenomC LIKE'%"+rech+"%' or DescriptionR LIKE'%"+rech+"%' ");

    return model;


}

QSqlQueryModel* reclamation::afficherNomCdesc()
{
    QSqlQueryModel* model=new QSqlQueryModel;
          model->setQuery("SELECT * FROM RECLAMATION ORDER by NomC DESC  ;");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDR"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("NomC"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("PrenomC"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DescriptionR"));

    return model;
}
QSqlQueryModel* reclamation::afficherNomCasc()
{
    QSqlQueryModel* model=new QSqlQueryModel;
          model->setQuery("SELECT * FROM RECLAMATION ORDER by NomC ASC  ;");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDR"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("NomC"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("PrenomC"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DescriptionR"));

    return model;
}
