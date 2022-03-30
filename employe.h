#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class employe
{

    int id,numtel;
    QString prenom,nom,adresse;
public:
    employe();
    employe(int id,QString nom,QString prenom,int numtel,QString adresse);
    bool rech(int a);

    bool ajouter();
    bool modifier(int);
    bool supprimer(int);
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficherTri(QString);
    QSqlQueryModel * afficherRech(QString,QString);
};

#endif // EMPLOYE_H
