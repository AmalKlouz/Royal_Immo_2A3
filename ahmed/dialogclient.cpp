#include "dialogclient.h"
#include "ui_dialogclient.h"
#include "client.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
DialogClient::DialogClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogClient)
{
    ui->setupUi(this);
    int ret=a.connect_arduino();//connecter a arduino
          switch (ret) {     //afficher un message selon shneya sar fl cnx
          case(0):qDebug()<<"arduino is available and connected to :"<<a.getarduino_port_name();
              break;
          case(1):qDebug()<<"arduino is available but not connected to :"<<a.getarduino_port_name();
              break;
          case(-1):qDebug()<<"arduino is not available";
          }
    QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));//waqteli arduino yab3ath information ysir appelle ll fct update_label()
    connect(ui->rech, SIGNAL(textChanged(QString)), this, SLOT(affrech()));
    QFile file("c:/HistoriqueA.txt");
   if (!file.open(QIODevice::ReadOnly))
   {        QMessageBox::information(0,"info",file.errorString());    }
   QTextStream in (&file);
  ui->textBrowser->setText(in.readAll());
     ui->tableClient->setModel(tmpc.afficher());
     QIntValidator *roll = new QIntValidator(10000000,99999999);


     ui->CIN->setValidator(roll);
     ui->Numtel->setValidator(roll);
}

DialogClient::~DialogClient()
{
    delete ui;
}
void DialogClient::update_label()//hedhi bsh n3aytoulha k l arduino ybaaeth haja
{
data.append(a.read_from_arduino());//lvariable data bsh yetkteb fih ennoumrou lnzlt aalih
qDebug()<<data;
if(data.length()==8){//yverifi estceque houma 8 arqam

if(tmpc.rech(data)){//waqtha ycharchi fl BD



    a.write_to_arduino("1");//b3athna les infos ll arduino  OUT
    data.clear();//yfaragh lvariable data
    qDebug()<<"ok";
}else  {data.clear();
 a.write_to_arduino("0");}//OUT
}
}
void DialogClient::on_Button_ajouter_client_clicked()
{
    int cin=ui->CIN->text().toInt();
    QString nom=ui->Nom->text();
    QString prenom=ui->Prenom->text();
    QString adresse=ui->Adresse->text();
    int numtel=ui->Numtel->text().toInt();
    client c(cin,nom,prenom,adresse,numtel,fileName);
    QFile file1("c:/HistoriqueA.txt");

        if(!file1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
            return;


        QTextStream cout(&file1);
    bool test=c.ajouter();
    if(test){
        QString message2="\nVous avez ajouté un client le "+QDateTime::currentDateTime().toString();
            cout << message2;
            QFile file("c:/HistoriqueA.txt");
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
void DialogClient::affrech(){
    ui->tableClient->setModel(tmpc.afficherRech(ui->comboBoxTriRech->currentText(),ui->rech->text()));

}
void DialogClient::on_Button_modifier_client_clicked()
{
    int cin=ui->CIN->text().toInt();
    QString nom=ui->Nom->text();
    QString prenom=ui->Prenom->text();
    QString adresse=ui->Adresse->text();
    int numtel=ui->Numtel->text().toInt();
    client c(cin,nom,prenom,adresse,numtel,fileName);
    QFile file1("c:/HistoriqueA.txt");

        if(!file1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
            return;


        QTextStream cout(&file1);
    bool test=c.modifier(QString::number(cin));
    if(test){
        QString message2="\nVous avez modifié un client le "+QDateTime::currentDateTime().toString();
            cout << message2;
            QFile file("c:/HistoriqueA.txt");
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

void DialogClient::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    QFile file("c:/HistoriqueA.txt");
   if (!file.open(QIODevice::ReadOnly))
   {        QMessageBox::information(0,"info",file.errorString());    }
   QTextStream in (&file);
  ui->textBrowser->setText(in.readAll());
}

void DialogClient::on_pushButton_clicked()
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

void DialogClient::on_buttonSupprimer_client_clicked()
{
    QFile file1("c:/HistoriqueA.txt");
       if(!file1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
           return;


       QTextStream cout(&file1);


       int row =ui->tableClient->selectionModel()->currentIndex().row();
              QString cin=ui->tableClient->model()->index(row,0).data().toString();
              tmpc.supprimer(cin);
               ui->tableClient->setModel(tmpc.afficher());
               QString message2="\nVous avez supprimé un client le "+QDateTime::currentDateTime().toString();
                   cout << message2;
                   QFile file("c:/HistoriqueA.txt");
                  if (!file.open(QIODevice::ReadOnly))
                  {        QMessageBox::information(0,"info",file.errorString());    }
                  QTextStream in (&file);
                 ui->textBrowser->setText(in.readAll());

}

void DialogClient::on_recuperer_clicked()
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
             QPixmap pix(q.value(5).toString());
             ui->img->setPixmap(pix);
     }
}

void DialogClient::on_TrierClient_clicked()
{
      ui->tableClient->setModel(tmpc.afficherTri(ui->comboBoxTriRech->currentText()));
}

void DialogClient::on_pushButton_4_clicked()
{
    fileName = QFileDialog::getSaveFileName((QWidget* )0, "Importer image", QString(), "*.jpg");
   QPixmap pix(fileName);
   ui->img->setPixmap(pix);
}

void DialogClient::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
