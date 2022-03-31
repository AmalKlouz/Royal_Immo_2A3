#include "bien.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <unistd.h>
 bien::bien()
{


 }
bien::bien(int id_imo,QString typeC,QString dateC,int prix,QString DescriptionB)
{
    this->id_imo=id_imo;this->typeC=typeC;this->dateC=dateC;this->prix=prix;this->DescriptionB=DescriptionB;

}

int bien::getid_imo(){return id_imo;}
QString bien::gettypeC(){return typeC;}
QString bien::getdateC(){return dateC;}
int bien::getprix(){return prix;}

QString bien::getDescriptionB(){return  DescriptionB;}
void bien::setid_imo(int id_imo){this->id_imo=id_imo;}
//void bien ::setimage(QImage image) {this->image=image;}
void bien::settypeC(QString typeC){this->typeC=typeC;}
void bien::setdateC(QString dateC){this->dateC=dateC;}
void bien::setprix(int prix){this->prix=prix;}
void bien::setDescriptionB(QString DescriptionB){this->DescriptionB=DescriptionB;}








bool bien::ajouter()
{

    QString id_imo_string=QString::number(id_imo);
    QString prix_string=QString::number(prix);
        QSqlQuery query;

        query.clear();
if (id_imo ==0)
{
    QMessageBox::critical(nullptr, QObject::tr("chaine vide!"),
                QObject::tr("L'identifiant est vide"), QMessageBox::Cancel);

    return  false;
}

/*if ((typeC != "avendre") ||( typeC !="AVENDRE") ||( typeC !="alouer") ||( typeC !="ALOUER"))
{
    QMessageBox::critical(nullptr, QObject::tr("type non valide type doit etre  avendre ou alouer!"),
                QObject::tr("type non valide type doit etre  avendre ou alouer!"), QMessageBox::Cancel);

    return  false;
}*/

if (typeC =="")
{
    QMessageBox::critical(nullptr, QObject::tr("chaine vide!"),
                QObject::tr("type est vide"), QMessageBox::Cancel);

    return  false;
}


if (prix ==0)
{
    QMessageBox::critical(nullptr, QObject::tr("chaine vide!"),
                QObject::tr("prix obligatoire"), QMessageBox::Cancel);

    return  false;
}






         query.prepare("INSERT INTO BIEN ("
                       "ID_IMO,"
                       "PRIX,"
                       "TYPEC,"
                       "DATEC,"
                       "DESCRIPTIONB)"
                       "VALUES (:id_imo ,:prix, :typeC, :datec, :DescriptionB);");
         query.bindValue(0, id_imo_string);

         query.bindValue(2, typeC);
         query.bindValue(3, dateC);
         query.bindValue(1, prix_string);
         query.bindValue(4, DescriptionB);

        //query.bindValue(5,image, byte, Q);
         return  query.exec();
}
QSqlQueryModel* bien::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel;
          model->setQuery("SELECT * FROM BIEN");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_imo"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("typeC"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("dateC"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DescriptionB"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("image"));

    return model;
}
int bien::supprimer(int id)
{
    QSqlQuery requete;


  int row_count = 0;
  bool test;
    requete.prepare("SELECT COUNT(*) FROM BIEN WHERE ID_IMO=?");
    requete.addBindValue(id);
    test = requete.exec();
    if(requete.first())
        row_count = requete.value(0).toInt();
    qDebug() << row_count;
    if(test == true && row_count !=0)
    {

      requete.prepare("DELETE FROM BIEN WHERE ID_IMO=?");
      requete.addBindValue(id);
      requete.exec();
      qDebug() << "Suppression effectué avec succés" ;
      QMessageBox::information(nullptr,QObject::tr("Suppression") , QObject::tr("Le bien a bien été supprimer !"),QMessageBox::Ok );
      return 1;

    }
    else if(test == true && row_count==0)
    {
        qDebug() << id << " n'existe pas et donc ne peux pas etre supprime";
        QMessageBox::critical(nullptr,QObject::tr("Suppresion") , QObject::tr("Identifiant inexistant"),QMessageBox::Cancel );
        return 0;
    }
    else
    {
        qDebug() << "erreur de suppresion";
        QMessageBox::critical(nullptr,QObject::tr("Suppresion") , QObject::tr("Erreur de suppresion"),QMessageBox::Cancel );
        return 0;
    }

  //qDebug() << test;



}




bool bien::check_idE(int id)
{
    QSqlQuery requete;


  int row_count = 0;
  bool test;
    requete.prepare("SELECT COUNT(*) FROM BIEN WHERE ID_IMO=?");
    requete.addBindValue(id);
    test = requete.exec();
    if(requete.first())
        row_count = requete.value(0).toInt();
    qDebug() << row_count;
    if(test == true && row_count !=0)
    {


      //qDebug() << "l'id mawjouda" ;
      //QMessageBox::information(nullptr,QObject::tr("Suppresion") , QObject::tr("id mawjoud!"),QMessageBox::Ok );

      return  true;

    }
    else if(test == true && row_count==0)
    {
        qDebug() << id << " id inexistante ";
        QMessageBox::critical(nullptr,QObject::tr("Modification") , QObject::tr("Identifiant inexistant"),QMessageBox::Cancel );
        return  false;
    }
    else
    {
        qDebug() << "erreur de modification";
        QMessageBox::critical(nullptr,QObject::tr("Modification") , QObject::tr("Erreur de recherche"),QMessageBox::Cancel );
    }
}
bool bien::update(int id,int prix,QString Description,QString type,QString date)
{

    if (id ==0)
    {
        QMessageBox::critical(nullptr, QObject::tr("chaine vide!"),
                    QObject::tr("L'identifiant est vide"), QMessageBox::Cancel);

        return  false;
    }
    if (prix ==0)
    {
        QMessageBox::critical(nullptr, QObject::tr("chaine vide!"),
                    QObject::tr("prix obligatoire"), QMessageBox::Cancel);

        return  false;
    }
   if (type =="")
    {
        QMessageBox::critical(nullptr, QObject::tr("chaine vide!"),
                    QObject::tr("type est vide"), QMessageBox::Cancel);

        return  false;
    }







QSqlQuery req;
req.prepare("UPDATE BIEN SET PRIX=? where ID_IMO=?");
req.addBindValue(prix);
req.addBindValue(id);
req.exec();
req.clear();
req.prepare("UPDATE BIEN SET TYPEC=? where ID_IMO=?");
req.addBindValue(type);
req.addBindValue(id);
req.exec();
req.clear();
req.prepare("UPDATE BIEN SET DESCRIPTIONB=? where ID_IMO=?");
req.addBindValue(Description);
req.addBindValue(id);
req.exec();
req.clear();
req.prepare("UPDATE BIEN SET DATEC=? where ID_IMO=?");
req.addBindValue(date);
req.addBindValue(id);
req.exec();
req.clear();
QMessageBox::information(nullptr,QObject::tr("Modification") , QObject::tr("L'article a bien été modifier !"),QMessageBox::Ok );
return true;
}


QSqlQueryModel* bien::afficherprixasc()
{
    QSqlQueryModel* model=new QSqlQueryModel;
          model->setQuery("SELECT * FROM BIEN ORDER by prix ASC;");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_imo"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("typeC"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("dateC"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DescriptionB"));

    return model;
}
QSqlQueryModel* bien::afficherprixdesc()
{
    QSqlQueryModel* model=new QSqlQueryModel;
          model->setQuery("SELECT * FROM BIEN ORDER by prix DESC  ;");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_imo"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("typeC"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("dateC"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DescriptionB"));

    return model;
}
/*
bool::bien
QSqlQueryModel *bien::afficher a_vendre (){
    QSqlQueryModel* model=new QSqlQueryModel;
          model->setQuery("SELECT * FROM BIEN where typeC ="AVENDRE" ;");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_imo"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("typeC"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("dateC"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DescriptionB"));


    return model;
}

*/





QSqlQueryModel* bien::rechercher(QString rech)
{
    QSqlQueryModel *model= new QSqlQueryModel();
   // model->setQuery("SELECT * FROM BIEN WHERE prix LIKE'%"+rech+"%'");
 model->setQuery("SELECT * FROM BIEN WHERE  prix LIKE'%"+rech+"%' or id_imo LIKE'%"+rech+"%' or typeC LIKE'%"+rech+"%' or datec LIKE'%"+rech+"%'");
   //  model->setQuery("SELECT * FROM BIEN WHERE id_imo LIKE'%"+rech+"%'");

     // model->setQuery("SELECT * FROM BIEN WHERE typeC LIKE'%"+rech+"%'");

       // model->setQuery("SELECT * FROM BIEN WHERE datec LIKE'%"+rech+"%'");
       // sleep(2);
    return model;


}
