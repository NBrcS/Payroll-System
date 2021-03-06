#ifndef FINALEDIT_H
#define FINALEDIT_H

#include <QDialog>
#include "empresa.h"
#include <QMessageBox>


namespace Ui {
class finaledit;
}

class finaledit : public QDialog
{
    Q_OBJECT

public:
    explicit finaledit(QWidget *parent = nullptr, Empresa *Empresa_ = nullptr, int index = 0);
    ~finaledit();

private slots:
    void on_radio_Manager_toggled(bool checked);

    void on_radio_Director_toggled(bool checked);

    void on_radio_President_toggled(bool checked);

    void clear_Morphys();

    void clear_bools();

    void clear_all_edits();

    void select_func(int);

    void att_list();

    void on_bt_att_clicked();

    void on_radio_Operator_toggled(bool checked);

    void on_listWidget_infoExihibiton_currentRowChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::finaledit *ui;

    bool president, director, manager, operador;
    QString designation;

    Empresa *empresa;
    int index;
};

#endif // FINALEDIT_H
