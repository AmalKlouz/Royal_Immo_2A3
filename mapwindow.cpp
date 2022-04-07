#include "mapwindow.h"
#include "ui_mapwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"qvariant.h"
#include <QQuickItem>
#include<QVariant>
mapwindow::mapwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mapwindow)
{
    ui->setupUi(this);

    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    ui->quickWidget->show();
    auto obj = ui->quickWidget->rootObject();
    connect(this ,SIGNAL(setCenter(QVariant,QVariant)),obj,SLOT(setCenter(qvarient,qvarient)));
    emit setCenter(25.000,50.000);
}

mapwindow::~mapwindow()
{
    delete ui;
}
