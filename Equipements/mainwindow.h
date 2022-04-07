#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "equipement.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Add_button_clicked();

    void on_delete_btn_clicked();



    void on_pushButton_AjouterLink_clicked();

    void on_update_btn_clicked();

    void on_Update_button_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_tri_id_clicked();

    void on_tri_nom_clicked();

    void on_tri_date_ajout_clicked();

    void on_pdf_btn_clicked();

    void on_send_mail_clicked();

    void on_id_comboBox_currentTextChanged(const QString &arg1);

    void on_QR_btn_clicked();

    void on_Recherche_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Equipement E,Etmp;
};
#endif // MAINWINDOW_H
