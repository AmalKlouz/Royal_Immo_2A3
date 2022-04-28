#ifndef RECLAMATION_H
#define RECLAMATION_H


#include <QSqlQueryModel>
#include <QString>
#include <QDialog>
//#include <supprimerR.h>
class reclamation
{
public:
    reclamation();
     reclamation(int,QString,QString,int,QString);
     int getCIN();

     QString getNomC();
     QString getPrenomC();
    int getIDR();
     QString getDescriptionR();
    void setCIN(int);

    void setNomC(QString);
    void setPrenomC(QString);
    void setIDR(int);
    void setDescriptionR(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();

    QSqlQueryModel *rechercher(QString);

    QSqlQueryModel* afficherNomCdesc();
    QSqlQueryModel* afficherNomCasc();
private:
    int CIN,IDR;
    QString NomC,PrenomC,DescriptionR;
};

#endif // RECLAMATION_H
