#ifndef SUPPRIMERR_H
#define SUPPRIMERR_H
#include <QDialog>
#include <QSqlQueryModel>
#include <QString>
#include <reclamation.h>
#include "mainwindow.h"
namespace Ui {
class supprimerR;
}

class supprimerR : public QDialog
{
    Q_OBJECT

public:
    explicit supprimerR(QWidget *parent = nullptr);
    ~supprimerR();


private slots:
    void on_pb_supprimer_clicked();


private:
    Ui::supprimerR *ui;
};

#endif // SUPPRIMERR_H
