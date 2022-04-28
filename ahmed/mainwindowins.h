#ifndef MAINWINDOWINS_H
#define MAINWINDOWINS_H

#include <QMainWindow>
#include "user.h"
namespace Ui {
class MainWindowIns;
}

class MainWindowIns : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowIns(QWidget *parent = nullptr);
    ~MainWindowIns();
   void afficherBD();
private slots:
    void on_pushButton_clicked();

    void on_commandLinkButton_clicked();

private:
    Ui::MainWindowIns *ui;
     user tmpu;
};

#endif // MAINWINDOWINS_H
