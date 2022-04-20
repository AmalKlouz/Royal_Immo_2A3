#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>


class Equipement
{
    QString marque,type,etat;
    int id;
public:
    Equipement();
    Equipement(int,QString,QString,QString);

    int getID();
    QString getMarque();
    QString getType();
    QString getEtat();

    void setID(int );
    void setMarque(QString );
    void setType(QString );
    void setEtat(QString );

    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(int);
    bool update(int,QString,QString,QString);
    QSqlQueryModel* rechercher(const QString &aux);
    bool add_barcode(int,QString);
};

#endif // EQUIPEMENT_H
