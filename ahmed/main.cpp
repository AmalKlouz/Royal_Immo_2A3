#include <QDebug>
#include "mainwindowins.h"
#include <QApplication>
#include <QMessageBox>
#include "connexion.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    connexion c;
    bool test=c.createconnect();
    MainWindowIns w;
        w.show();

    return a.exec();
}
