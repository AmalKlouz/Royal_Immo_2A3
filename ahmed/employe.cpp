#include "employe.h"
#include <QDebug>
employe::employe()
{

}
employe::employe(int id,QString nom,QString prenom,int numtel,QString adresse,QString mdp)
{
this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->numtel=numtel;
    this->adresse=adresse;
    this->mdp=mdp;
}
bool employe::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO EMPLOYE VALUES(:id,:nom,:prenom,:numtel,:adresse,:mdp)");
     query.bindValue(":id",id);
     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":numtel",numtel);
     query.bindValue(":adresse",adresse);
      query.bindValue(":mdp",mdp);
    return query.exec();
}
bool employe::modifier(int id)
{
    if(!rech(id)){return false;}
    QSqlQuery query;
QString sql="update EMPLOYE set nom=:nom,prenom=:prenom,numtel=:numtel,adresse=:adresse,mdp=:mdp where id=:id";
qDebug()<<sql;
    query.prepare(sql);
     query.bindValue(":id",id);
     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":numtel",numtel);
     query.bindValue(":adresse",adresse);
     query.bindValue(":mdp",mdp);
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
bool employe::connecter(int id, QString mdp)
{
    QString sql="select * from employe where id="+QString::number(id)+" AND mdp='"+mdp+"'";
    QSqlQuery q(sql);
    qDebug()<<sql;
    while(q.next())return true;
    return false;
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
