#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include "dialogreclamation.h"
#include "equipmentdialog.h"
#include "dialogbien.h"
namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_rec_clicked();

    void on_bien_m_clicked();

    void on_equipement_clicked();

private:
    Ui::Menu *ui;
     dialogreclamation *secdialog;
     dialogbien *bienndialog;
     EquipmentDialog *equipementDialog;
};

#endif // MENU_H
