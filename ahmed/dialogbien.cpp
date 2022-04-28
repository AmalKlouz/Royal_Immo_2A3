#include "dialogbien.h"
#include "ui_dialogbien.h"
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
#include "arduino.h"
#include "arduino1.h"
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

dialogbien::dialogbien(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dialogbien)
{
    ui->setupUi(this);
}
void dialogbien::afficherBD()
{
    bien afe;
    arduino1 a;
     //ui->table_bien->setModel(afe.afficher());
    ui->table_bien->setModel(afe.afficher());
//ui->table_ard->setModel(a.afficherARD());
}

dialogbien::~dialogbien()
{
    delete ui;
}
void dialogbien::videz_label()
{
    ui->le_id->setText("");
    ui->le_idS->setText("");
    ui->le_date->setText("");
    ui->le_prix->setText("");
    //ui->le_type->setText("");
    ui->le_Description->setText("");

}

void dialogbien::on_pushButton_clicked()
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




void dialogbien::on_pushButton_4_clicked()
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
void dialogbien::on_pushButton_3_clicked()
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
//prix men louta lel fouk
void dialogbien::on_radioButton_clicked()
{

    if (ui->radioButton->isChecked())
    {
        bien afe;
         ui->table_bien->setModel(afe.afficherprixasc());
    }
}

// prix men fouk lel louta
void dialogbien::on_radioButton_2_clicked()
{

    if (ui->radioButton_2->isChecked())
    {
        bien aff;
         ui->table_bien->setModel(aff.afficherprixdesc());
    }
}
//recherche
void dialogbien::on_rech_textChanged(const QString &arg1)
{
    bien t;
       ui->table_bien->setModel(t.rechercher(arg1));
}

void dialogbien::on_exporter_clicked()
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

}

void dialogbien::on_excel_clicked()
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


void dialogbien::on_mapbutton_clicked()
{
     mapwindow1= new mapwindow(this);
       mapwindow1->show();
}

void dialogbien::on_recuperer_clicked()
{

    int row =ui->table_bien->selectionModel()->currentIndex().row();
               QString ID_IMO=ui->table_bien->model()->index(row,0).data().toString();
               QSqlQuery q("select * from BIEN where ID_IMO="+ID_IMO);


                while(q.next())
                {

                    ui->le_id->setText(q.value(0).toString());
                     //ui->comboBox->showPopup(q.value(2).toString());
                 //  ui->dateEdit->setDate(q.value(3).toDate());
ui->le_date->setText(q.value(3).toString());
                    ui->comboBox->setCurrentText(q.value(2).toString());
                       // ui->comboBox->setCurrentText(setmodal)
                      ui->le_prix->setText(q.value(1).toString());
                       ui->le_Description->setText(q.value(4).toString());
                   //     ui->le_Description_2->setText(q.value(4).toString());
                }

}

void dialogbien::on_table_bien_activated(const QModelIndex &index)
{

    QString val=ui->table_bien->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("select * from bien where id_imo='"+val+"'");

        if (qry.exec())
        {
            while (qry.next())
            {
                ui->le_idS->setText(qry.value(0).toString());

            }
        }
}

void dialogbien::on_pushButton_2_clicked()
{
    bien afe;
         ui->table_bien->setModel(afe.afficher());
}
