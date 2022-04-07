#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QMainWindow>
#include<QVariant>

namespace Ui {
class mapwindow;
}

class mapwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mapwindow(QWidget *parent = nullptr);
    ~mapwindow();

private:
    Ui::mapwindow *ui;
signals:
    void setCenter(QVariant,QVariant);

};

#endif // MAPWINDOW_H
