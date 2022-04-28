#ifndef ACCEUIL_H
#define ACCEUIL_H

#include <QDialog>
#include "employe.h"
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
namespace Ui {
class acceuil;
}

class acceuil : public QDialog
{
    Q_OBJECT

public:
    explicit acceuil(QWidget *parent = nullptr);
    ~acceuil();
private slots:
    void on_ButtonAjouterEmploye_clicked();

    void on_ButtonModifierEmploye_clicked();

    void on_ButtonSupprimerEmploye_clicked();

    void on_recuperer_clicked();

    void on_Exporter_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
    void affrech();

private:
    Ui::acceuil *ui;
    employe tmpe;
};

#endif // ACCEUIL_H
