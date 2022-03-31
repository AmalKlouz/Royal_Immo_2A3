#ifndef BIEN_H
#define BIEN_H
#include <QSqlQueryModel>
#include <QString>


class bien
{
public:
    bien();
     bien(int,QString,QString,int,QString);
     int getid_imo();

     QString gettypeC();
     QString getdateC();
    int getprix();
     QString getDescriptionB();


      // QImage  getimage(image);
     //  void setimage(QImage);
    void setid_imo(int);

    void settypeC(QString);
    void setdateC(QString);
    void setprix(int);
    void setDescriptionB(QString);
    bool ajouter();
    QSqlQueryModel* rechercher(QString);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficherprixasc();
    QSqlQueryModel* afficherprixdesc();
    int supprimer(int id);
    bool check_idE(int id);
    bool update(int id,int prix,QString Description,QString type,QString date);
private:
    int prix,id_imo;
    QString typeC,dateC,DescriptionB;
   // QImage image;


};

#endif // BIEN_H
