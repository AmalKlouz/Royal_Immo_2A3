#include "reclamation.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QTranslator t;
    Connection c;
       bool test=c.createconnect();
    QStringList languages;

    languages << "French" << "English" << "Portugais" ;
    QString lang = QInputDialog::getItem(NULL,"Select Language","Language",languages);
    if (lang == "English" )
    {
        t.load(":/english.qm");


    }else if ( lang == "Portugais")
    {
        t.load(":/portugais.qm");
    }

    if ( lang != "French")
    {
        a.installTranslator(&t);
    }

    if(test)
    {
        w.show();
}






    return a.exec();
}
