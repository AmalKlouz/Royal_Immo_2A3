#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bien.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void afficherBD();
    void videz_label();

private slots:
    void on_pb_Ajouter_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_Supprimer_clicked();

    void on_le_id_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_table_bien_clicked(const QModelIndex &index);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_rech_textChanged(const QString &arg1);

    void on_exporter_clicked();

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_imagebouton_clicked();

    void on_excel_clicked();

private:
    Ui::MainWindow *ui;




};


#endif // MAINWINDOW_H
