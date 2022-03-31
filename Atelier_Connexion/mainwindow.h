#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <modifierR.h>
#include <QMainWindow>
#include <supprimerR.h>

#include "notification.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_Ajouter_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_Supprimer_clicked();

    void on_modifier_clicked();

    void on_Reclamation_activated(const QModelIndex &index);

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_le_id_supp_textChanged(const QString &arg1);

    void on_loaddata_clicked();

    void on_recuperer_clicked();

    void on_exporter_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_triID_2_clicked();

    void on_trinomASC_clicked();

    void on_trinomDESC_clicked();

    void on_apparaitre_clicked();

private:
    Ui::MainWindow *ui;
     PopUp *popUp;
};


#endif // MAINWINDOW_H
