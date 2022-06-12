#ifndef FINALEDIT_H
#define FINALEDIT_H

#include <QDialog>
#include "data.h"


namespace Ui {
class finaledit;
}

class finaledit : public QDialog
{
    Q_OBJECT

public:
    explicit finaledit(QWidget *parent = nullptr, Data* data_ = nullptr);
    ~finaledit();

private slots:
    void on_radio_Manager_toggled(bool checked);

    void on_radio_Director_toggled(bool checked);

    void on_radio_President_toggled(bool checked);

    void clear_Morphys();

    void clear_bools();

    void select_func(int);

    void att_list();

    void on_bt_att_clicked();

    void on_radio_Operator_toggled(bool checked);

    void receber_dados(Data&);

private:
    Ui::finaledit *ui;

    bool president, director, manager, operador;

    Data* data;
};

#endif // FINALEDIT_H