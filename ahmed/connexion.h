#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

//commit commit hh 3
class connexion
{private : QSqlDatabase db;
public:
    connexion();
     bool createconnect();
     void fermerconnexion();
};

#endif // CONNEXION_H
