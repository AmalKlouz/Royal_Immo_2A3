#ifndef MAINWINDOWINS_H
#define MAINWINDOWINS_H

#include <QMainWindow>
#include "employe.h"
namespace Ui {
class MainWindowIns;
}

class MainWindowIns : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowIns(QWidget *parent = nullptr);
    ~MainWindowIns();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindowIns *ui;
     employe tmpe;
};

#endif // MAINWINDOWINS_H
