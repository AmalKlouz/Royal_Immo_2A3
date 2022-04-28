#include <QDebug>
#include "mainwindowins.h"
#include <QApplication>
#include <QMessageBox>
#include "connexion.h"
#include "dialogbien.h"
#include "equipmentdialog.h"
#include "ui_dialogbien.h"
#include"mapwindow.h"
#include "bien.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // MainWindow w;
    connexion c;
    bool test=c.createconnect();
    MainWindowIns w;
      MainWindowIns f;
    if(test){

        w.show();
          //f.afficherBD();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    return a.exec();
}
