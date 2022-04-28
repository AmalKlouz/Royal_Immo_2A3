#ifndef DIALOGBIEN_H
#define DIALOGBIEN_H
#include "mapwindow.h"
#include <QMainWindow>

namespace Ui {
class dialogbien;
}

class dialogbien : public QMainWindow
{
    Q_OBJECT

public:
    explicit dialogbien(QWidget *parent = nullptr);
    ~dialogbien();
    void afficherBD();
    void afficherARD();
    void videz_label();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_rech_textChanged(const QString &arg1);

    void on_exporter_clicked();

    void on_excel_clicked();

    void on_mapbutton_clicked();

    void on_recuperer_clicked();

    void on_table_bien_activated(const QModelIndex &index);

    void on_pushButton_2_clicked();

private:
    Ui::dialogbien *ui;
    QByteArray data; // variable contenant les données reçues
    mapwindow *mapwindow1;
  //Arduino A;

};

#endif // DIALOGBIEN_H
