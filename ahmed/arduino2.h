#ifndef ARDUINO2_H
#define ARDUINO2_H
#include<QDateTime>


class arduino2{
public:
    arduino2 (QString date1){this->date_ajout=date1;};
bool ajouter();
QString date_ajout;
};
#endif // ARDUINO2_H
