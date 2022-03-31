#ifndef MODIFIERR_H
#define MODIFIERR_H

#include <QDialog>

namespace Ui {
class modifierR;
}

class modifierR : public QDialog
{
    Q_OBJECT

public:
    explicit modifierR(QWidget *parent = nullptr);
    ~modifierR();

private slots:
    void on_pb_recherche_clicked();

    void on_pb_modifier_clicked();

private:
    Ui::modifierR *ui;
};

#endif // MODIFIERR_H
