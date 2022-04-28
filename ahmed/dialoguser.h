#ifndef DIALOGUSER_H
#define DIALOGUSER_H
#include "arduino.h"
#include <QDialog>
#include "user.h"
namespace Ui {
class DialogUser;
}

class DialogUser : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUser(QWidget *parent = nullptr);
    ~DialogUser();

private slots:

    void on_ButtonModifierUser_clicked();

    void on_ButtonAjouterUser_clicked();

    void on_recupererUser_clicked();

    void on_ButtonSupprimerUser_clicked();

private:
    Ui::DialogUser *ui;
    user tmpu;
    arduino a;
};

#endif // DIALOGUSER_H
