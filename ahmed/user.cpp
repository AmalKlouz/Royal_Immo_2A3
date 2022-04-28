#include "user.h"
#include <QDebug>
user::user()
{

}
user::user(int id,QString email,QString mdp)
{
this->id=id;
    this->email=email;
    this->mdp=mdp;
}
bool user::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO utilisateur VALUES(:id,:email,:mdp)");
     query.bindValue(":id",id);
     query.bindValue(":email",email);
      query.bindValue(":mdp",mdp);
    return query.exec();
}
bool user::modifier(int id)
{
    if(!rech(id)){return false;}
    QSqlQuery query;
QString sql="update utilisateur set email=:email,mdp=:mdp where id=:id";
qDebug()<<sql;
    query.prepare(sql);
     query.bindValue(":id",id);
     query.bindValue(":email",email);
     query.bindValue(":mdp",mdp);
    return query.exec();
}
QSqlQueryModel *user::afficher()
{

    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select id,email from utilisateur");
    return model;
}

bool user::rech(int a)
{
    QSqlQuery q1;
    QString res=QString::number(a);
    q1.exec("select *from utilisateur where id='"+res+"'");
    bool test=q1.next();
    return test;
}
bool user::connecter(QString email, QString mdp)
{
    QString sql="select * from utilisateur where email='"+email+"' AND mdp='"+mdp+"'";
    QSqlQuery q(sql);
    qDebug()<<sql;
    while(q.next())return true;
    return false;
}
bool user::supprimer(int id)
{
    if(!rech(id)){return false;}
    QSqlQuery query;

    QString res=QString::number(id);
    query.prepare("Delete from utilisateur where id=:id");
    query.bindValue(":id",res);
    return query.exec();
}
