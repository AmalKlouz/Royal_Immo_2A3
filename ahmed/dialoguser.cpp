#include "dialoguser.h"
#include "ui_dialoguser.h"
#include <QMessageBox>
#include <regex>
DialogUser::DialogUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUser)
{
    ui->setupUi(this);
     ui->tableUser->setModel(tmpu.afficher());


      QIntValidator *roll1 = new QIntValidator(10000000,99999999);

     ui->ID->setValidator(roll1);
}

DialogUser::~DialogUser()
{
    delete ui;
}



void DialogUser::on_ButtonModifierUser_clicked()
{

    int id=ui->ID->text().toInt();
    QString email=ui->EMAIL->text();
    QString mdp=ui->MDP->text();
    user e(id,email,mdp);
    bool test=e.modifier(id);
    if(test)
    {  ui->tableUser->setModel(tmpu.afficher());
        QMessageBox::information(nullptr,QObject::tr("modifier user"),
                               QObject::tr("user modifié"),QMessageBox::Ok);

    }else
        QMessageBox::critical(nullptr,QObject::tr("modifier user"),
                                      QObject::tr("user non modifié"),QMessageBox::Ok);
}

void DialogUser::on_ButtonAjouterUser_clicked()
{

    int id=ui->ID->text().toInt();
    QString email=ui->EMAIL->text();
    QString mdp=ui->MDP->text();
    user e(id,email,mdp);
    const QRegExp pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    if(mdp.length()>8){
        if( pattern.exactMatch(email)){

    bool test=e.ajouter();
    if(test)
    {  ui->tableUser->setModel(tmpu.afficher());
        QMessageBox::information(nullptr,QObject::tr("Ajouter user"),
                               QObject::tr("user ajouté"),QMessageBox::Ok);

    }else
        QMessageBox::critical(nullptr,QObject::tr("Ajouter user"),
                                      QObject::tr("user non ajouté"),QMessageBox::Ok);}
        else QMessageBox::critical(nullptr,QObject::tr("Ajouter user"),
                                   QObject::tr("email invalide"),QMessageBox::Ok);}
    else QMessageBox::critical(nullptr,QObject::tr("Ajouter user"),
                               QObject::tr("mdp invalide"),QMessageBox::Ok);
}

void DialogUser::on_recupererUser_clicked()
{

    int row =ui->tableUser->selectionModel()->currentIndex().row();
           QString id=ui->tableUser->model()->index(row,0).data().toString();
           QSqlQuery q("select * from utilisateur where id="+id);


            while(q.next())
            {
                ui->ID->setText(q.value(0).toString());

                    ui->EMAIL->setText(q.value(1).toString());
                     ui->MDP->setText(q.value(2).toString());
            }
}

void DialogUser::on_ButtonSupprimerUser_clicked()
{

    int row =ui->tableUser->selectionModel()->currentIndex().row();
           int id=ui->tableUser->model()->index(row,0).data().toInt();
           tmpu.supprimer(id);
            ui->tableUser->setModel(tmpu.afficher());
}
