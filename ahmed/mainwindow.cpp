#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <QtPrintSupport/QPrinter>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextDocument>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPieSeries *series = new QPieSeries();
    QSqlQuery q("select adresse,count(*) from employe group by adresse");


     while(q.next())
     {series->append(q.value(0).toString()+": "+q.value(1).toString(),q.value(1).toInt());}
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques");
    chart->setBackgroundBrush(Qt::transparent);
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setParent(ui->horizontalFrame);
    chartview->resize(400,300);

    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    series->setLabelsVisible(true);
    ui->tableEmploye->setModel(tmpe.afficher());
    QIntValidator *roll = new QIntValidator(100000,999999);
     QIntValidator *roll1 = new QIntValidator(10000000,99999999);

    ui->ID->setValidator(roll);
    ui->NUMTEL->setValidator(roll1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ButtonAjouterEmploye_clicked()
{
    int id=ui->ID->text().toInt();
    QString nom=ui->NOM->text();
    QString prenom=ui->PRENOM->text();
    int numtel=ui->NUMTEL->text().toInt();
    QString adresse=ui->ADRESSE->text();
    QString mdp=ui->MDP->text();
    employe e(id,nom,prenom,numtel,adresse,mdp);
    bool test=e.ajouter();
    if(test)
    {  ui->tableEmploye->setModel(tmpe.afficher());
        QMessageBox::information(nullptr,QObject::tr("Ajouter employe"),
                               QObject::tr("employe ajouté"),QMessageBox::Ok);

    }else
        QMessageBox::critical(nullptr,QObject::tr("Ajouter employe"),
                                      QObject::tr("employe non ajouté"),QMessageBox::Ok);
}


void MainWindow::on_ButtonModifierEmploye_clicked()
{
    int id=ui->ID->text().toInt();
    QString nom=ui->NOM->text();
    QString prenom=ui->PRENOM->text();
    int numtel=ui->NUMTEL->text().toInt();
    QString adresse=ui->ADRESSE->text();
    QString mdp=ui->MDP->text();
    employe e(id,nom,prenom,numtel,adresse,mdp);
    bool test=e.modifier(id);
    if(test)
    { ui->tableEmploye->setModel(tmpe.afficher());
        QMessageBox::information(nullptr,QObject::tr("Modifier employe"),
                               QObject::tr("employe modifié"),QMessageBox::Ok);

    }else
        QMessageBox::critical(nullptr,QObject::tr("Modifier employe"),
                                      QObject::tr("employe non modifié"),QMessageBox::Ok);
}


void MainWindow::on_ButtonSupprimerEmploye_clicked()
{
    int row =ui->tableEmploye->selectionModel()->currentIndex().row();
           int id=ui->tableEmploye->model()->index(row,0).data().toInt();
           tmpe.supprimer(id);
            ui->tableEmploye->setModel(tmpe.afficher());
}


void MainWindow::on_recuperer_clicked()
{
    int row =ui->tableEmploye->selectionModel()->currentIndex().row();
           QString id=ui->tableEmploye->model()->index(row,0).data().toString();
           QSqlQuery q("select * from employe where id="+id);


            while(q.next())
            {
                ui->ID->setText(q.value(0).toString());
                 ui->NOM->setText(q.value(1).toString());
                  ui->PRENOM->setText(q.value(2).toString());
                   ui->NUMTEL->setText(q.value(3).toString());
                    ui->ADRESSE->setText(q.value(4).toString());
            }
}


void MainWindow::on_Exporter_clicked()
{
    QString strStream;
                   QTextStream out(&strStream);

                    const int rowCount = ui->tableEmploye->model()->rowCount();
                    const int columnCount = ui->tableEmploye->model()->columnCount();
                   out <<  "<html>\n"
                   "<head>\n"
                                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                    <<  QString("<title>%1</title>\n").arg("strTitle")
                                    <<  "</head>\n"
                                    "<body bgcolor=#ffffff link=#5000A0>\n"

                                   //     "<align='right'> " << datefich << "</align>"
                                    "<center> <H1>Liste des employEs</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                // headers
                                out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                out<<"<cellspacing=10 cellpadding=3>";
                                for (int column = 0; column < columnCount; column++)
                                    if (!ui->tableEmploye->isColumnHidden(column))
                                        out << QString("<th>%1</th>").arg(ui->tableEmploye->model()->headerData(column, Qt::Horizontal).toString());
                                out << "</tr></thead>\n";

                                // data table
                                for (int row = 0; row < rowCount; row++) {
                                    out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                    for (int column = 0; column < columnCount; column++) {
                                        if (!ui->tableEmploye->isColumnHidden(column)) {
                                            QString data = ui->tableEmploye->model()->data(ui->tableEmploye->model()->index(row, column)).toString().simplified();
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


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->tableEmploye->setModel(tmpe.afficherTri(ui->critere->currentText()));
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->tableEmploye->setModel(tmpe.afficherRech(ui->critere->currentText(),ui->lineEditRech->text()));
}

