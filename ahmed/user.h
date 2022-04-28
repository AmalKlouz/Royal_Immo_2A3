#ifndef USER_H
#define USER_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class user
{

    int id;
    QString email,mdp;
public:
    user();
    user(int id,QString email,QString mdp);
    bool rech(int a);
    bool connecter(QString,QString);
    bool ajouter();
    bool modifier(int);
    bool supprimer(int);
    QSqlQueryModel * afficher();
};

#endif // USER_H
