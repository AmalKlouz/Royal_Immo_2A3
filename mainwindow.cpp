#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mapwindow.h"
#include "bien.h"
#include<QPdfWriter>
#include <unistd.h>
#include <QPainter>
#include <QTextStream>
#include <QtPrintSupport/QPrinter>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextDocument>
#include<QFileDialog>
#include <QDateTime>
#include<QTextDocument>
#include <QTextEdit>

#include <QtSql/QSqlQueryModel>

#include<QtPrintSupport/QPrinter>

#include <QVector2D>

#include <QVector>

#include <QSqlQuery>

#include<QDesktopServices>

#include <QMessageBox>

#include<QUrl>
#include<QQuickWidget>

#include <QPixmap>

#include <QTabWidget>

#include <QValidator>

#include<QtSql/QSqlQuery>

#include<QVariant>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Gestion des biens");
    QPixmap pix("");

}

/*void MainWindow::on_mapbutton_clicked()
{
    mapwindow = new mapwindow(this);
    mapwindow->show();

}*/


void MainWindow::afficherBD()
{
    bien afe;
     ui->table_bien->setModel(afe.afficher());

}




MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_Ajouter_clicked()
{
   /*ui->le_id->text().toInt();
        imo = ui->
QString typeC=ui->le_type->text();
QString dateC=ui->le_date->text();
int prix=ui->le_prix->text().toInt();
QString DescriptionB=ui->le_Description->text();
    bien b(id_imo,typeC,dateC,prix,DescriptionB);
    bool test=B.ajouter();
    if(test)

    {
        QMessageBox::information(nullptr, QObject::tr("add is ok"),
                    QObject::tr(" successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("add not ok"),
                    QObject::tr(" failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);*/

}

void MainWindow::videz_label()
{
    ui->le_id->setText("");
    ui->le_idS->setText("");
    ui->le_date->setText("");
    ui->le_prix->setText("");
    //ui->le_type->setText("");
    ui->le_Description->setText("");

}

/*

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    bien a;
 //  QString typeC;
   QString typeC=ui->comboBox->currentText();



}



*/

//BOUTON AJOUTER
void MainWindow::on_pushButton_clicked()
{

    int id_imo=ui->le_id->text().toInt();


  //  QString typeC=ui->le_type->text();
    //QString typeC=ui->le_type->text();
QString typeC=ui->comboBox->currentText();

//QString typeC;
  //  QString datec=ui->le_date;
QString dateC=ui->dateEdit->text();

   // QString dateC=sysdate;
    int prix=ui->le_prix->text().toInt();
    QString DescriptionB=ui->le_Description->text();
   // QImage image = ui->imageLabel->pixmap()->toImage();
        bien b(id_imo,typeC,dateC,prix,DescriptionB);
        bool test=b.ajouter();

        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("add is ok"),
                        QObject::tr(" successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            videz_label();


    }

        else if ((b.check_idE(id_imo)==true)  )
        {
            QMessageBox::critical(nullptr, QObject::tr("Deja existant!"),
                        QObject::tr("L'identifiant existe deja"), QMessageBox::Cancel);
        }
        /*
        else if(b.check()==true)
        {QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                                                   QObject::tr("CHAMP VIDE de id .\n" "Click Cancel to exit."), QMessageBox::Cancel);
}
*/
        bien afe;
        ui->table_bien->setModel(afe.afficher());

}

void MainWindow::on_pushButton_2_clicked()
{
    /*bien afe;
     ui->table_bien->setModel(afe.afficher());*/
}
//BOUTON SUPPRIMER
void MainWindow::on_pushButton_4_clicked()
{
    int test = 0;
    bien E1;

    E1.setid_imo(ui->le_idS->text().toInt());
    test = E1.supprimer(E1.getid_imo());
    bien afe;
     ui->table_bien->setModel(afe.afficher());
     videz_label();


}
//BOUTON MODIFIER
void MainWindow::on_pushButton_3_clicked()
{
    int id = ui->le_id->text().toInt();
    bool ba=false;
    bool bc=false;

bien af;
 ba = af.check_idE(id);
 if(ba)
 {

      bc = af.update(id,ui->le_prix->text().toInt(),ui->le_Description->text(),ui->comboBox->currentText(),ui->le_date->text());
      // bc = af.update(id,ui->le_prix->text().toInt(),ui->le_Description->text(),ui->le_type->text(),ui->le_date->text());
      ui->table_bien->setModel(af.afficher());
      videz_label();







 }
}

/*void MainWindow::on_table_bien_clicked(const QModelIndex &index)
{

}*/
//prix men louta lel fouk
void MainWindow::on_radioButton_clicked()
{

        if (ui->radioButton->isChecked())
        {
            bien afe;
             ui->table_bien->setModel(afe.afficherprixasc());
        }

}

// prix men fouk lel louta
void MainWindow::on_radioButton_2_clicked()
{

    if (ui->radioButton_2->isChecked())
    {
        bien aff;
         ui->table_bien->setModel(aff.afficherprixdesc());
    }

}

/*
void MainWindow::on_table_bien_clicked(const QModelIndex &index)
{

}
*/




void MainWindow::on_rech_textChanged(const QString &arg1)
{
    {
        bien t;
           ui->table_bien->setModel(t.rechercher(arg1));
    }
}

void MainWindow::on_exporter_clicked()
{
    QString strStream;
                      QTextStream out(&strStream);

                       const int rowCount = ui->table_bien->model()->rowCount();
                       const int columnCount = ui->table_bien->model()->columnCount();
                      out <<  "<html>\n"
                      "<head>\n"
                                       "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                       <<  QString("<title>%1</title>\n").arg("strTitle")
                                       <<  "</head>\n"
                                       "<body bgcolor=#ffffff link=#5000A0>\n"

                                      //     "<align='right'> " << datefich << "</align>"
                                       "<center> <H1>bien immobillier </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                   // headers
                                   out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                   out<<"<cellspacing=10 cellpadding=3>";
                                   for (int column = 0; column < columnCount; column++)
                                       if (!ui->table_bien->isColumnHidden(column))
                                           out << QString("<th>%1</th>").arg(ui->table_bien->model()->headerData(column, Qt::Horizontal).toString());
                                   out << "</tr></thead>\n";

                                   // data table
                                   for (int row = 0; row < rowCount; row++) {
                                       out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                       for (int column = 0; column < columnCount; column++) {
                                           if (!ui->table_bien->isColumnHidden(column)) {
                                               QString data = ui->table_bien->model()->data(ui->table_bien->model()->index(row, column)).toString().simplified();
                                               out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                           }
                                       }
                                       out << "</tr>\n";
                                   }
                                   out <<  "</table> </center>\n"
                                       "</body>\n"
                                       "</html>\n";

                             QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                               if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                              QPrinter printer (QPrinter::PrinterResolution);
                               printer.setOutputFormat(QPrinter::PdfFormat);
                              printer.setPaperSize(QPrinter::A4);
                             printer.setOutputFileName(fileName);

                              QTextDocument doc;
                               doc.setHtml(strStream);
                               doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                               doc.print(&printer);

   /////////////
}



/*void MainWindow::on_imagebouton_clicked()
{


}
*/

void MainWindow::on_imagebouton_clicked()
{
    QFileDialog dialog(this);
 dialog.setNameFilter(tr("Image (*.png *.xpm *.jpg"));
 dialog.setViewMode(QFileDialog::Detail);
 QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),"home/rpi/Desktop/picture/sample Pictures",tr("Image Files(*.png *.jpg"));
ui->imageLabel->setPixmap(QPixmap(fileName));
this->adjustSize();
}



/*
void MainWindow::on_imagebouton_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                     "fichier ",
                                     ".",
                                     "Fichier (*.png)");
   // ui->imageLabel->setPixmap(QPixmap(fileName));
    QFileInfo fi(fileName);
   // ui->fileNameLabel->setText(fi.fileName());
   //QString image=fileName.;
    QApplication::processEvents();
    this->adjustSize();
}
*/





 void MainWindow::on_excel_clicked()
{

    QTableView *table;
                       table = ui->table_bien;


                       QString filters("CSV files (.csv);;All files (.*)");
                                     QString defaultFilter("CSV files (*.csv)");
                       QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                          filters, &defaultFilter);
                       QFile file(fileName);

                       QAbstractItemModel *model =  table->model();
                       if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                           QTextStream data(&file);
                           QStringList strList;
                           for (int i = 0; i < model->columnCount(); i++) {
                               if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                                   strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                               else
                                   strList.append("");
                           }
                           data << strList.join(";") << "\n";
                           for (int i = 0; i < model->rowCount(); i++) {
                               strList.clear();
                               for (int j = 0; j < model->columnCount(); j++) {

                                   if (model->data(model->index(i, j)).toString().length() > 0)
                                       strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                                   else
                                       strList.append("");
                               }
                               data << strList.join(";") + "\n";
                           }
                           file.close();
                           QMessageBox::information(nullptr, QObject::tr("Import excel"),
                                                     QObject::tr("Import avec succes .\n"
                                                                 "Click OK to exit."), QMessageBox::Ok);
                       }

}

void MainWindow::on_mapbutton_clicked()
{
    //mapwindow mapwindow1;
   // mapwindow= new mapwindow1(this);
    mapwindow1= new mapwindow(this);
   // mapwindow1.setModal(true);
   // mapwindow1.exec();
    mapwindow1->show();

}

void MainWindow::on_recuperer_clicked()
{

        int row =ui->table_bien->selectionModel()->currentIndex().row();
                   QString ID_IMO=ui->table_bien->model()->index(row,0).data().toString();
                   QSqlQuery q("select * from BIEN where ID_IMO="+ID_IMO);


                    while(q.next())
                    {

                        ui->le_id->setText(q.value(0).toString());
                         //ui->comboBox->showPopup(q.value(2).toString());
                      //  ui->dateEdit->setDate(q.value(2));

                          ui->le_prix->setText(q.value(1).toString());
                           ui->le_Description->setText(q.value(4).toString());
                       //     ui->le_Description_2->setText(q.value(4).toString());
                    }




}
