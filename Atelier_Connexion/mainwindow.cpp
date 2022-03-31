#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reclamation.h"
#include "connection.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QMessageBox>
#include <QTextStream>
#include <QtPrintSupport/QPrinter>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextDocument>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    popUp = new PopUp();
    reclamation R;
ui->Reclamation->setModel(R.afficher());
//place holder text
ui->lineEdit->setPlaceholderText("Ecrire le nom que vous souhaitez le chercher");

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_Ajouter_clicked()
{
   int CIN=ui->le_CIN->text().toInt();

QString NomC=ui->le_nom->text();
QString PrenomC=ui->le_prenom->text();
int IDR=ui->le_IDR->text().toInt();
QString DescriptionC=ui->le_Description->text();
    reclamation R(CIN,NomC,PrenomC,IDR,DescriptionC);
    bool test=R.ajouter();
    if(test)
    {
        popUp->setPopupText("une réclamation a été ajouter ");


        popUp->setGeometry (QApplication::desktop () ->width () - 36 - popUp->width (),
                              QApplication::desktop () ->height () - 52 - popUp->height (),


                           popUp->width (),
                           popUp->height ()) ;

           popUp->show();

}
    else
    popUp->setPopupText("une reclamation n'a pas été ajoutée");


    popUp->setGeometry (QApplication::desktop () ->width () - 36 - popUp->width (),
                          QApplication::desktop () ->height () - 52 - popUp->height (),


                       popUp->width (),
                       popUp->height ()) ;

       popUp->show();

}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    reclamation R;
    ui->Reclamation->setModel(R.afficher());

}

void MainWindow::on_Supprimer_clicked()
{
    reclamation R1; R1.setIDR(ui->le_IDR_2->text().toInt());
    bool test=R1.supprimer(R1.getIDR());
    if(test)
    {

        popUp->setPopupText("une reclamation a  été supprimer ");


        popUp->setGeometry (QApplication::desktop () ->width () - 36 - popUp->width (),
                              QApplication::desktop () ->height () - 52 - popUp->height (),


                           popUp->width (),
                           popUp->height ()) ;

           popUp->show();
    }
    else
        popUp->setPopupText("une reclamation n'a pas été supprimer");


        popUp->setGeometry (QApplication::desktop () ->width () - 36 - popUp->width (),
                              QApplication::desktop () ->height () - 52 - popUp->height (),


                           popUp->width (),
                           popUp->height ()) ;

           popUp->show();
}
void MainWindow::on_recuperer_clicked()
{
    int row =ui->Reclamation->selectionModel()->currentIndex().row();
               QString CIN=ui->Reclamation->model()->index(row,0).data().toString();
               QSqlQuery q("select * from RECLAMATION where CIN="+CIN);


                while(q.next())
                {

                    ui->le_IDR_2->setText(q.value(1).toString());
                     ui->le_nom_2->setText(q.value(2).toString());
                      ui->le_prenom_2->setText(q.value(3).toString());
                       ui->le_CIN_2->setText(q.value(0).toString());
                        ui->le_Description_2->setText(q.value(4).toString());
                }



}

void MainWindow::on_modifier_clicked()
{

    QSqlQueryModel *modal=new QSqlQueryModel;
        QSqlQuery *qry=new QSqlQuery;
        qry->prepare("select IDR from RECLAMATION");
        qry->exec();
        modal->setQuery(*qry);
        int IDR=ui->le_IDR_2->text().toInt();
        QString NomC=ui->le_nom_2->text();
        QString PrenomC=ui->le_prenom_2->text();
        int CIN=ui->le_CIN_2->text().toInt();

        QString DescriptionR=ui->le_Description_2->text();
         reclamation R2(CIN,NomC,PrenomC,IDR,DescriptionR);
         bool test=R2.modifier();
         if(test)
         {
             popUp->setPopupText("une reclamation a  été modifier");


             popUp->setGeometry (QApplication::desktop () ->width () - 36 - popUp->width (),
                                   QApplication::desktop () ->height () - 52 - popUp->height (),


                                popUp->width (),
                                popUp->height ()) ;

                popUp->show();

         }
         else

             popUp->setPopupText("une reclamation n'a pas été modifier");


             popUp->setGeometry (QApplication::desktop () ->width () - 36 - popUp->width (),
                                   QApplication::desktop () ->height () - 52 - popUp->height (),


                                popUp->width (),
                                popUp->height ()) ;

                popUp->show();
}






void MainWindow::on_loaddata_clicked()
{
    QSqlQuery *qry=new QSqlQuery;
   QSqlQueryModel* modal=new QSqlQueryModel;

    qry->prepare("select *  from RECLAMATION ");

    qry->exec();
    modal->setQuery(*qry);
    ui->Reclamation->setModel(modal);

}


void MainWindow::on_exporter_clicked()
{

        QString strStream;
                       QTextStream out(&strStream);

                        const int rowCount = ui->Reclamation->model()->rowCount();
                        const int columnCount = ui->Reclamation->model()->columnCount();
                       out <<  "<html>\n"
                       "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                        <<  QString("<title>%1</title>\n").arg("strTitle")
                                        <<  "</head>\n"
                                        "<body bgcolor=#ffffff link=#5000A0>\n"

                                       //     "<align='right'> " << datefich << "</align>"
                                        "<center> <H1>Liste des reclamations</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                    // headers
                                    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                    out<<"<cellspacing=10 cellpadding=3>";
                                    for (int column = 0; column < columnCount; column++)
                                        if (!ui->Reclamation->isColumnHidden(column))
                                            out << QString("<th>%1</th>").arg(ui->Reclamation->model()->headerData(column, Qt::Horizontal).toString());
                                    out << "</tr></thead>\n";

                                    // data table
                                    for (int row = 0; row < rowCount; row++) {
                                        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                        for (int column = 0; column < columnCount; column++) {
                                            if (!ui->Reclamation->isColumnHidden(column)) {
                                                QString data = ui->Reclamation->model()->data(ui->Reclamation->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{

    reclamation R;
    ui->Reclamation->setModel(R.rechercher(arg1));

}



void MainWindow::on_trinomASC_clicked()
{
    if (ui->trinomASC->isChecked())
           {
               reclamation afe;
                ui->Reclamation->setModel(afe.afficherNomCasc());
           }
}

void MainWindow::on_trinomDESC_clicked()
{
    if (ui->trinomDESC->isChecked())
           {
               reclamation afe;
                ui->Reclamation->setModel(afe.afficherNomCdesc());
           }
}

/*void MainWindow::on_apparaitre_clicked()
{

    popUp->setPopupText(ui->le_CIN->text());


    popUp->setGeometry (QApplication::desktop () ->width () - 36 - popUp->width (),
                          QApplication::desktop () ->height () - 52 - popUp->height (),


                       popUp->width (),
                       popUp->height ()) ;

       popUp->show();
}
*/
