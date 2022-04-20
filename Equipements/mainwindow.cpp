#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipement.h"
#include <QMessageBox>
#include <QTableView>
#include <QTextStream>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextDocument>
#include <QPrinter>
#include <QSystemTrayIcon>
#include <QDebug>
#include <QSqlError>
#include <QtSvg/QSvgRenderer>
#include <QPainter>
#include <sstream>
#include <fstream>
#include "vector"
#include "qrcodegen.h"
#include "arduino.h"

using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;






MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel (E.afficher());

    //initially set current page to 0
        ui->stackedWidget->setCurrentIndex(1);

        connect(ui->pushButton_AjouterLink, &QPushButton::clicked, this, [=]() {
            //set page to 1
            ui->stackedWidget->setCurrentIndex(0);
        });

        connect(ui->Cancel_button, &QPushButton::clicked, this, [=]() {
            //set page to 1
            ui->stackedWidget->setCurrentIndex(1);
        });

        connect(ui->Cancel_button_2, &QPushButton::clicked, this, [=]() {
            //set page to 1
            ui->stackedWidget->setCurrentIndex(1);
        });


        connect(ui->Cancel_button_4, &QPushButton::clicked, this, [=]() {
            //set page to 1
            ui->stackedWidget->setCurrentIndex(1);
        });

        connect(ui->Add_button, &QPushButton::clicked, this, [=]() {
            //set page to 1
            ui->stackedWidget->setCurrentIndex(1);
        });
     connect(ui->update_btn, &QPushButton::clicked, this, [=]() {
           //set page to 2
            ui->stackedWidget->setCurrentIndex(2);
        });
     connect(ui->Update_button, &QPushButton::clicked, this, [=]() {
         //set page to 1
         ui->stackedWidget->setCurrentIndex(1);
     });
     connect(ui->arduino, &QPushButton::clicked, this, [=]() {
           //set page to 2
            ui->stackedWidget->setCurrentIndex(3);
        });
     connect(ui->addBarcode, &QPushButton::clicked, this, [=]() {
         //set page to 1
         ui->stackedWidget->setCurrentIndex(1);
     });

     QSqlQueryModel * modal=new QSqlQueryModel ();
     QSqlQuery* qry=new QSqlQuery ();
     qry->prepare ("select ID from EQUIPEMENT ");
     qry->exec ();
     modal->setQuery(*qry);
     ui->comboBox->setModel(modal);

     int ret=A.connect_arduino (); // lancer la connexion à arduino
     switch (ret){
     case (0):qDebug() << "arduino is available and connected to : " << A.getarduino_port_name();
         break;
     case(1):qDebug()<< "arduino is available but not connected to :" <<A.getarduino_port_name ();
        break;
     case (-1):qDebug() << "arduino is not available";
     }
      QObject::connect(A.getserial (),SIGNAL (readyRead ()), this,SLOT(update_label())); // permet de lancer
      //le slot update_label suite à la reception du signal readyRead (reception des données)

//     data=A.read_from_arduino();
//      ui->res_arduino->setText(data);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Add_button_clicked()
{
    ui->tableView->setModel (Etmp.afficher());
    int id=ui->eID->text().toInt ();
     QString marque =ui->e_marque->text();
     QString type =ui->e_type->currentText();
     QString etat="";
     if(ui->radioButton->isChecked()){etat =ui->radioButton->text();}
     else if (ui->radioButton_2->isChecked()){etat =ui->radioButton_2->text();}
     Equipement E(id,marque,type,etat);
     bool test=E.ajouter();
     if(test) {
         ui->tableView->setModel (E.afficher());
         QSqlQueryModel * modal=new QSqlQueryModel ();
         QSqlQuery* qry=new QSqlQuery ();
         qry->prepare ("select ID from EQUIPEMENT ");
         qry->exec ();
         modal->setQuery(*qry);
         ui->comboBox->setModel(modal);
          QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("Ajout efrectué\n"
                                     "citck Cancel to exit."), QMessageBox::Cancel);}
           else{
          QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                       QObject::tr("Ajout non effectué. \n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);}
}


void MainWindow::on_delete_btn_clicked()
{
    ui->tableView->setModel (Etmp.afficher());
    int val=ui->comboBox->currentText().toInt();
    Etmp.setID(val);
    bool test=Etmp.supprimer(Etmp.getID());
    if(test){
        QSqlQueryModel * modal=new QSqlQueryModel ();
        QSqlQuery* qry=new QSqlQuery ();
        qry->prepare ("select ID from EQUIPEMENT ");
        qry->exec ();
        modal->setQuery(*qry);
        ui->comboBox->setModel(modal);
        QMessageBox::information(nullptr, QObject::tr("OK"),
                      QObject::tr("Suppression effectuée\n"
                                      "ciick Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                       QObject::tr("Suppression non effectuée.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tableView->setModel (Etmp.afficher());


}





void MainWindow::on_pushButton_AjouterLink_clicked()
{

}

void MainWindow::on_update_btn_clicked()
{
    QSqlQueryModel * modal=new QSqlQueryModel ();
    QSqlQuery* qry=new QSqlQuery ();
    qry->prepare ("select ID from EQUIPEMENT where ID <>0");
    qry->exec ();
    modal->setQuery(*qry);
    ui->id_comboBox->setModel(modal);


}

void MainWindow::on_id_comboBox_currentTextChanged(const QString &arg1)
{

    int s_id=ui->id_comboBox->currentText().toInt();
    QString s_marque;
        QSqlQuery query1;
        query1.prepare("SELECT MARQUE FROM EQUIPEMENT where ID=?");
        query1.addBindValue(s_id);
        query1.exec();

        if(!query1.exec()) {
        qDebug() << "SQL Statement Error 2" << query1.lastError();
        }

        while (query1.next())
        {
          s_marque = query1.value(0).toString();
          break;
        }
        if(!query1.next()) {
        qDebug() << "SQL Statement Error 3" << query1.lastError();
        }


         ui->e_marque_2->setText(s_marque);

         QString s_type;
             QSqlQuery query2;
             query2.prepare("SELECT TYPE FROM EQUIPEMENT where ID=?");
             query2.addBindValue(s_id);
             query2.exec();

             if(!query2.exec()) {
             qDebug() << "SQL Statement Error 2" << query2.lastError();
             }

             while (query2.next())
             {
               s_type = query2.value(0).toString();
               break;
             }
             if(!query2.next()) {
             qDebug() << "SQL Statement Error 3" << query2.lastError();
             }


              ui->e_type_2->setCurrentText(s_type);

              QString s_etat;
                  QSqlQuery query3;
                  query3.prepare("SELECT ETAT FROM EQUIPEMENT where ID=?");
                  query3.addBindValue(s_id);
                  query3.exec();

                  if(!query3.exec()) {
                  qDebug() << "SQL Statement Error 2" << query3.lastError();
                  }

                  while (query3.next())
                  {
                    s_etat = query3.value(0).toString();
                    break;
                  }
                  if(!query3.next()) {
                  qDebug() << "SQL Statement Error 3" << query3.lastError();
                  }

                  if(s_etat=="Fonctionnel"){
                  ui->radioButton_3->setChecked(1);
                  }
                  else{
                  ui->radioButton_4->setChecked(1);
                  }


//                   ui->e_type_2->setCurrentText(s_type);


}

void MainWindow::on_Update_button_clicked()
{
    ui->tableView->setModel (Etmp.afficher());
     int s_id=ui->id_comboBox->currentText().toInt();
     QString marque =ui->e_marque_2->text();
     QString type =ui->e_type_2->currentText();
     QString etat="";
     if(ui->radioButton_3->isChecked()){etat =ui->radioButton_3->text();}
     else if (ui->radioButton_4->isChecked()){etat =ui->radioButton_4->text();}
            bool test = E.update(s_id,marque,type,etat);
            if (test)
                  {

                                   QMessageBox::information(nullptr, QObject::tr("OK"),
                                               QObject::tr("modification effectué.\n"
                                                           "Click Cancel to exit."), QMessageBox::Cancel);
                   }
                  else{
                  QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                          QObject::tr("modification non établie"),
                                          QMessageBox::Cancel);}
            ui->tableView->setModel(E.afficher());
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{

}

void MainWindow::on_tri_id_clicked()
{
    {
            QMessageBox msgBox ;
                    QSqlQueryModel * model= new QSqlQueryModel();


                       model->setQuery("select * from EQUIPEMENT where ID <> 0 order by ID");
                       model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
                       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
                       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Marque"));
                       model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat"));
                       model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date D'ajout"));


                                ui->tableView->setModel(model);
                                ui->tableView->show();
                                msgBox.setText("Tri avec succés.");
                                msgBox.exec();

                }
}

void MainWindow::on_tri_nom_clicked()
{
{
    QMessageBox msgBox ;
            QSqlQueryModel * model= new QSqlQueryModel();


               model->setQuery("select * from EQUIPEMENT where ID <> 0 order by LOWER(MARQUE)");
               model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
               model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("Marque"));
               model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat"));
               model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date D'ajout"));


                        ui->tableView->setModel(model);
                        ui->tableView->show();
                        msgBox.setText("Tri avec succés.");
                        msgBox.exec();

        }
}

void MainWindow::on_tri_date_ajout_clicked()
{
    {
    QMessageBox msgBox ;
            QSqlQueryModel * model= new QSqlQueryModel();


               model->setQuery("select * from EQUIPEMENT where ID <> 0 order by DATE_AJOUT");
               model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
               model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("Marque"));
               model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat"));
               model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date D'ajout"));


                        ui->tableView->setModel(model);
                        ui->tableView->show();
                        msgBox.setText("Tri avec succés.");
                        msgBox.exec();

        }
}

void MainWindow::on_pdf_btn_clicked()
{
    QString strStream;
           QTextStream out(&strStream);

           const int rowCount = ui->tableView->model()->rowCount();
           const int columnCount = ui->tableView->model()->columnCount();

           out <<  "<html>\n"
               "<head>\n"
               "<meta Content=\"Text/html; charset=Windows-1251\">\n"
               <<  QString("<title>%1</title>\n").arg("strTitle")
               <<  "</head>\n"
               "<body bgcolor=#ffffff link=#5000A0>\n"

               //     "<align='right'> " << datefich << "</align>"
               "<center> <H1>Liste des Equipements </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

           // headers
           out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
           for (int column = 0; column < columnCount; column++)
               if (!ui->tableView->isColumnHidden(column))
                   out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
           out << "</tr></thead>\n";

           // data table
           for (int row = 0; row < rowCount; row++)
           {
               out << "<tr> <td bkcolor=0>" << row + 1 << "</td>";
               for (int column = 0; column < columnCount; column++)
               {
                   if (!ui->tableView->isColumnHidden(column))
                   {
                       QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                       out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                   }
               }
               out << "</tr>\n";
           }
           out <<  "</table> </center>\n"
               "</body>\n"
               "</html>\n";

           QString fileName = QFileDialog::getSaveFileName((QWidget * )0, "Sauvegarder en PDF", QString(), "*.pdf");
           if (QFileInfo(fileName).suffix().isEmpty())
           {
               fileName.append(".pdf");
           }

           QPrinter printer (QPrinter::PrinterResolution);
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setPaperSize(QPrinter::A4);
           printer.setOutputFileName(fileName);

           QTextDocument doc;
           doc.setHtml(strStream);
           doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
           doc.print(&printer);

}


void MainWindow::on_QR_btn_clicked()
{
    int val=ui->comboBox->currentText().toInt();
    QString s_id=ui->comboBox->currentText();

    QString s_marque;
        QSqlQuery query1;
        query1.prepare("SELECT MARQUE FROM EQUIPEMENT where ID=?");
        query1.addBindValue(val);
        query1.exec();

        if(!query1.exec()) {
        qDebug() << "SQL Statement Error 2" << query1.lastError();
        }

        while (query1.next())
        {
          s_marque = query1.value(0).toString();
          break;
        }
        if(!query1.next()) {
        qDebug() << "SQL Statement Error 3" << query1.lastError();
        }


         ui->e_marque_2->setText(s_marque);

         QString s_type;
             QSqlQuery query2;
             query2.prepare("SELECT TYPE FROM EQUIPEMENT where ID=?");
             query2.addBindValue(val);
             query2.exec();

             if(!query2.exec()) {
             qDebug() << "SQL Statement Error 2" << query2.lastError();
             }

             while (query2.next())
             {
               s_type = query2.value(0).toString();
               break;
             }
             if(!query2.next()) {
             qDebug() << "SQL Statement Error 3" << query2.lastError();
             }


              ui->e_type_2->setCurrentText(s_type);

              QString s_etat;
                  QSqlQuery query3;
                  query3.prepare("SELECT ETAT FROM EQUIPEMENT where ID=?");
                  query3.addBindValue(val);
                  query3.exec();

                  if(!query3.exec()) {
                  qDebug() << "SQL Statement Error 2" << query3.lastError();
                  }

                  while (query3.next())
                  {
                    s_etat = query3.value(0).toString();
                    break;
                  }
                  if(!query3.next()) {
                  qDebug() << "SQL Statement Error 3" << query3.lastError();
                  }

                  QString s_barcode;
                      QSqlQuery query4;
                      query4.prepare("SELECT BARCODE FROM EQUIPEMENT where ID=?");
                      query4.addBindValue(val);
                      query4.exec();

                      if(!query4.exec()) {
                      qDebug() << "SQL Statement Error 2" << query4.lastError();
                      }

                      while (query4.next())
                      {
                        s_barcode = query4.value(0).toString();
                        break;
                      }
                      if(!query4.next()) {
                      qDebug() << "SQL Statement Error 3" << query4.lastError();
                      }

        QString txt= "id:"+s_id+"/"+"MARQUE:"+s_marque+"/"+"TYPE:"+s_type+"/"+"ETAT:"+s_etat+"/"+"BARCODE:"+s_barcode;
        QByteArray ba = txt.toLocal8Bit();
          const char *c_str2 = ba.data();
 const QrCode qr0 = QrCode::encodeText(c_str2, QrCode::Ecc::MEDIUM);
 std::ofstream myfile;
                     myfile.open ("qrcode.svg") ;
                     myfile << qr0.toSvgString(1);
                     myfile.close();
                     QSvgRenderer svgRenderer(QString("qrcode.svg"));
                     QPixmap pix( QSize(90, 90) );
                     QPainter pixPainter( &pix );
                     svgRenderer.render( &pixPainter );
                     ui->QRCODE_4->setPixmap(pix);

}

void MainWindow::on_Recherche_textChanged(const QString &arg1)
{
    Equipement E;
    if(ui->Recherche->text() == " " )
            {
                ui->tableView->setModel(E.afficher());
            }
            else
            {
                 ui->tableView->setModel(E.rechercher(ui->Recherche->text()));
            }
}

void MainWindow::update_label()
{
   data=A.read_from_arduino();

if(!data.isNull()){
    qDebug() << data;
       d = QString::fromStdString(data.toStdString());
QStringList dd = d.split(" ");
QString ddd=dd[1]+dd[0];
   ui->res_arduino->setText(ddd);}
}

void MainWindow::on_addBarcode_clicked()
{

    ui->tableView->setModel (Etmp.afficher());
     int s_id=ui->eid->currentText().toInt();
     QString barcode=ui->res_arduino->text();
            bool test = E.add_barcode(s_id,barcode);
            if (test)
                  {

                                   QMessageBox::information(nullptr, QObject::tr("OK"),
                                               QObject::tr("Ajout du barcode effectué.\n"
                                                           "Click Cancel to exit."), QMessageBox::Cancel);
                   }
                  else{
                  QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                          QObject::tr("echec d'Ajout du barcode"),
                                          QMessageBox::Cancel);}
            ui->tableView->setModel(Etmp.afficher());

}

void MainWindow::on_arduino_clicked()
{
    QSqlQueryModel * modal=new QSqlQueryModel ();
    QSqlQuery* qry=new QSqlQuery ();
    qry->prepare ("select ID from EQUIPEMENT ");
    qry->exec ();
    modal->setQuery(*qry);
    ui->eid->setModel(modal);
}
