#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QDateTime>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file("HistoriqueA.txt");
   if (!file.open(QIODevice::ReadOnly))
   {        QMessageBox::information(0,"info",file.errorString());    }
   QTextStream in (&file);
  ui->textBrowser->setText(in.readAll());
     ui->tableClient->setModel(tmpc.afficher());
     QIntValidator *roll = new QIntValidator(10000000,99999999);


     ui->CIN->setValidator(roll);
     ui->Numtel->setValidator(roll);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Button_ajouter_client_clicked()
{
    int cin=ui->CIN->text().toInt();
    QString nom=ui->Nom->text();
    QString prenom=ui->Prenom->text();
    QString adresse=ui->Adresse->text();
    int numtel=ui->Numtel->text().toInt();
    client c(cin,nom,prenom,adresse,numtel);
    QFile file1("HistoriqueA.txt");
        qDebug()<<"eee";
        if(!file1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
            return;


        QTextStream cout(&file1);
    bool test=c.ajouter();
    if(test){
        QString message2="\nVous avez ajouté un client le "+QDateTime::currentDateTime().toString();
            cout << message2;
            QFile file("HistoriqueA.txt");
           if (!file.open(QIODevice::ReadOnly))
           {        QMessageBox::information(0,"info",file.errorString());    }
           QTextStream in (&file);
          ui->textBrowser->setText(in.readAll());
        ui->tableClient->setModel(tmpc.afficher());
        QMessageBox::information(nullptr, QObject::tr("Ajouter"),
                    QObject::tr("Client ajouté.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Ajouter"),
                    QObject::tr("Client non ajouté.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_Button_modifier_client_clicked()
{
    int cin=ui->CIN->text().toInt();
    QString nom=ui->Nom->text();
    QString prenom=ui->Prenom->text();
    QString adresse=ui->Adresse->text();
    int numtel=ui->Numtel->text().toInt();
    client c(cin,nom,prenom,adresse,numtel);
    QFile file1("HistoriqueA.txt");
        qDebug()<<"eee";
        if(!file1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
            return;


        QTextStream cout(&file1);


    QString ci=QString::number(cin);
    bool test=c.modifier(ci);
    if(test){
        QString message2="\nVous avez modifié un client le "+QDateTime::currentDateTime().toString();
            cout << message2;
            QFile file("HistoriqueA.txt");
           if (!file.open(QIODevice::ReadOnly))
           {        QMessageBox::information(0,"info",file.errorString());    }
           QTextStream in (&file);
          ui->textBrowser->setText(in.readAll());
        ui->tableClient->setModel(tmpc.afficher());
        QMessageBox::information(nullptr, QObject::tr("Ajouter"),
                    QObject::tr("Client modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Ajouter"),
                    QObject::tr("Client non modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_buttonSupprimer_client_clicked()
{ QFile file1("HistoriqueA.txt");
    if(!file1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;


    QTextStream cout(&file1);


    int row =ui->tableClient->selectionModel()->currentIndex().row();
           QString cin=ui->tableClient->model()->index(row,0).data().toString();
           tmpc.supprimer(cin);
            ui->tableClient->setModel(tmpc.afficher());
            QString message2="\nVous avez supprimé un client le "+QDateTime::currentDateTime().toString();
                cout << message2;
                QFile file("HistoriqueA.txt");
               if (!file.open(QIODevice::ReadOnly))
               {        QMessageBox::information(0,"info",file.errorString());    }
               QTextStream in (&file);
              ui->textBrowser->setText(in.readAll());

}

void MainWindow::on_recuperer_clicked()
{
    int row =ui->tableClient->selectionModel()->currentIndex().row();
    QString cin=ui->tableClient->model()->index(row,0).data().toString();
    QSqlQuery q("select * from client where cin="+cin);


     while(q.next())
     {
         ui->CIN->setText(q.value(0).toString());
          ui->Nom->setText(q.value(1).toString());
           ui->Prenom->setText(q.value(2).toString());
            ui->Adresse->setText(q.value(3).toString());
             ui->Numtel->setText(q.value(4).toString());
     }
}

void MainWindow::on_pushButton_clicked()
{
    QTableView *table;
       table = ui->tableClient;

       QString filters("CSV files (*.csv);;All files (*.*)");
       QString defaultFilter("CSV files (*.csv)");
       QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                          filters, &defaultFilter);
       fileName.append(".csv");
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
           QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
       }
}

void MainWindow::on_TrierClient_clicked()
{
    ui->tableClient->setModel(tmpc.afficherTri(ui->comboBoxTriRech->currentText()));
}

void MainWindow::on_rechercherClient_clicked()
{
     ui->tableClient->setModel(tmpc.afficherRech(ui->comboBoxTriRech->currentText(),ui->rech->text()));

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    QFile file("HistoriqueA.txt");
   if (!file.open(QIODevice::ReadOnly))
   {        QMessageBox::information(0,"info",file.errorString());    }
   QTextStream in (&file);
  ui->textBrowser->setText(in.readAll());
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
