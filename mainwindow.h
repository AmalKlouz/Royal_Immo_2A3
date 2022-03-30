#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
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
    void on_Button_ajouter_client_clicked();

    void on_Button_modifier_client_clicked();

    void on_buttonSupprimer_client_clicked();

    void on_recuperer_clicked();

    void on_pushButton_clicked();

    void on_TrierClient_clicked();

    void on_rechercherClient_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    client tmpc;
};

#endif // MAINWINDOW_H
