#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"
#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
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
    void on_ButtonAjouterEmploye_clicked();

    void on_ButtonModifierEmploye_clicked();

    void on_ButtonSupprimerEmploye_clicked();

    void on_recuperer_clicked();

    void on_Exporter_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    employe tmpe;
};
#endif // MAINWINDOW_H
