#ifndef EQUIPMENTDIALOG_H
#define EQUIPMENTDIALOG_H
#include "equipement.h"
#include "arduinoEQU.h"
#include <QMainWindow>

namespace Ui {
class EquipmentDialog;
}

class EquipmentDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit EquipmentDialog(QWidget *parent = nullptr);
    ~EquipmentDialog();
    void on_Add_button_clicked();

    void on_delete_btn_clicked();



    void on_pushButton_AjouterLink_clicked();


    void on_Update_button_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_tri_id_clicked();

    void on_tri_nom_clicked();

    void on_tri_date_ajout_clicked();

    void on_pdf_btn_clicked();

    void on_addBarcode_clicked();


    void on_QR_btn_clicked();

    void on_Recherche_textChanged(const QString &arg1);
    void update_label();

    void on_arduino_clicked();

private slots:
    void on_Add_button_equi_clicked();

    void on_RechercheEQUI_textChanged(const QString &arg1);

    void on_delete_equi_btn_clicked();

    void on_QR_equi_btn_clicked();

    void on_pdf_equi_btn_clicked();

    void on_tri_id_equi_clicked();

    void on_tri_nom_equi_clicked();

    void on_tri_date_ajout_equi_clicked();

    void on_UpdateEQUI_button_clicked();
    void on_update_btn_clicked();
    void on_id_comboBox_currentTextChanged(const QString &arg1);



private:
    Ui::EquipmentDialog *ui;
    QByteArray data;
    QString d;
    ArduinoEQU A;
    Equipement E,Etmp;
};



#endif // EQUIPMENTDIALOG_H
