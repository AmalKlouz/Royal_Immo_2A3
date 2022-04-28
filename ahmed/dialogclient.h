#ifndef DIALOGCLIENT_H
#define DIALOGCLIENT_H
#include "client.h"
#include <QDialog>
#include "arduino.h"
namespace Ui {
class DialogClient;
}

class DialogClient : public QDialog
{
    Q_OBJECT

public:
    explicit DialogClient(QWidget *parent = nullptr);
    ~DialogClient();

private slots:
    void affrech();
    void on_Button_ajouter_client_clicked();

    void on_Button_modifier_client_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_buttonSupprimer_client_clicked();

    void on_recuperer_clicked();

    void on_TrierClient_clicked();

    void on_pushButton_4_clicked();
    void update_label();

    void on_pushButton_3_clicked();

private:
    Ui::DialogClient *ui;
    client tmpc;
    QString fileName;
    arduino a;
        QByteArray data;
};

#endif // DIALOGCLIENT_H
