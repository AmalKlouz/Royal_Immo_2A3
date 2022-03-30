#include "employe.h"
#include <QDebug>
employe::employe()
{

}
employe::employe(int id,QString nom,QString prenom,int numtel,QString adresse)
{
this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->numtel=numtel;
    this->adresse=adresse;
}
bool employe::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO EMPLOYE VALUES(:id,:nom,:prenom,:numtel,:adresse)");
     query.bindValue(":id",id);
     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":numtel",numtel);
     query.bindValue(":adresse",adresse);
    return query.exec();
}
bool employe::modifier(int id)
{
    if(!rech(id)){return false;}
    QSqlQuery query;
QString sql="update EMPLOYE set nom=:nom,prenom=:prenom,numtel=:numtel,adresse=:adresse where id=:id";
qDebug()<<sql;
    query.prepare(sql);
     query.bindValue(":id",id);
     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":numtel",numtel);
     query.bindValue(":adresse",adresse);
    return query.exec();
}
QSqlQueryModel *employe::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select *from employe");
    return model;
}
QSqlQueryModel *employe::afficherTri(QString selon)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select *from employe order by "+selon);
    return model;
}
QSqlQueryModel *employe::afficherRech(QString selon,QString rech)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select *from employe where "+selon+" like '"+rech+"%'");
    return model;
}
bool employe::rech(int a)
{
    QSqlQuery q1;
    QString res=QString::number(a);
    q1.exec("select *from employe where id='"+res+"'");
    bool test=q1.next();
    return test;
}
bool employe::supprimer(int id)
{
    if(!rech(id)){return false;}
    QSqlQuery query;

    QString res=QString::number(id);
    query.prepare("Delete from employe where id=:id");
    query.bindValue(":id",res);
    return query.exec();
}
