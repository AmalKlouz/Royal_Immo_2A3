#include "equipement.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>

Equipement::Equipement()
{
id=0;
marque="";
type="";
etat="";
}

Equipement::Equipement(int eID,QString e_marque,QString e_type,QString etat)
{
this->id=eID;
this->marque=e_marque;
this->type=e_type;
this->etat=etat;
}

int Equipement::getID(){return id;}
QString Equipement::getMarque(){return marque;}
QString Equipement::getType(){return type;}
QString Equipement::getEtat(){return etat;}

void Equipement::setID(int id){this->id=id;}
void Equipement::setMarque(QString m){this->marque=m;}
void Equipement::setType(QString t){this->type=t;}
void Equipement::setEtat(QString e){this->etat=e;}


bool Equipement::ajouter()
{
bool test=false;
QSqlQuery query;
    QString eid= QString::number(id);
          query.prepare("INSERT INTO EQUIPEMENT (id, marque, type,etat) "
                        "VALUES (:id, :marque, :type, :etat)");
          query.bindValue(":id", eid);
          query.bindValue(":type", type);
          query.bindValue(":marque", marque);
          query.bindValue(":etat", etat);
        return query.exec();


    return test;

}

QSqlQueryModel * Equipement::afficher()
{
   QSqlQueryModel * model=new QSqlQueryModel();
         model->setQuery("SELECT * FROM EQUIPEMENT where ID <> 0");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("Marque"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date D'ajout"));

  return model;
}

bool  Equipement::supprimer(int id)
{  QSqlQuery query;
    query.prepare("delete from EQUIPEMENT where id=:id");
  query.bindValue(":id", id);
return query.exec();


}

bool Equipement::update(int ID,QString MARQUE,QString TYPE,QString ETAT)
{
    QSqlQuery query;
        query.prepare("UPDATE EQUIPEMENT SET TYPE=:TYPE,MARQUE=:MARQUE,ETAT=:ETAT WHERE ID=:ID");
        query.bindValue(":ID", ID);
        query.bindValue(":TYPE", TYPE);
        query.bindValue(":MARQUE", MARQUE);
        query.bindValue(":ETAT", ETAT);

        return    query.exec();
}

QSqlQueryModel* Equipement::rechercher (const QString &aux)

{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from EQUIPEMENT where ((ID||type||marque||etat) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Marque"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date D'ajout"));


    return model;

}