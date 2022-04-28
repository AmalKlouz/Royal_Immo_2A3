#ifndef DIALOGRECLAMATION_H
#define DIALOGRECLAMATION_H

#include <QMainWindow>

#include <QMainWindow>
#include "reclamation.h"
 #include "arduino1.h"
#include "notification.h"
namespace Ui {
class dialogreclamation;
}

class dialogreclamation : public QMainWindow
{
    Q_OBJECT

public:
    explicit dialogreclamation(QWidget *parent = nullptr);
    ~dialogreclamation();

private slots:
    void on_AjouterRec_clicked();
        void on_tabWidget_currentChanged(int index);

        void on_Supprimer_clicked();

        void on_recuperer_clicked();

        void on_modifier_clicked();

        void on_loaddata_clicked();

        void on_exporter_clicked();

        void on_lineEdit_textChanged(const QString &arg1);

        void on_trinomASC_clicked();

        void on_trinomDESC_clicked();

        void on_stop_clicked();
          void update_label();
private:
    Ui::dialogreclamation *ui;
    PopUp *popUp;
    QByteArray data; // variable contenant les données reçues

   arduino1 A; // objet temporaire
};

#endif // DIALOGRECLAMATION_H
