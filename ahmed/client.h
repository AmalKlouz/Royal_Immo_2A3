#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include<QSqlQueryModel>
class client
{
public:
    client();
    client(int cin,QString nom,QString prenom,QString adresse,int numtel,QString img);
    bool ajouter();
    bool supprimer(QString cin);
    bool rech(QString a);
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficherTri(QString);
    QSqlQueryModel * afficherRech(QString,QString);
    bool modifier(QString rech1);
    QString retournerInfos(QString);
int cin;
QString nom,prenom,adresse,img;
int numtel;
};

#endif // CLIENT_H
