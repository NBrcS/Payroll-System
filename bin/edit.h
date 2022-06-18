#ifndef EDIT_H
#define EDIT_H

#include <QDialog>
#include "empresa.h"
#include "signals.h"
#include <QMessageBox>

namespace Ui {
class edit;
}

class edit : public QDialog
{
    Q_OBJECT

public:
    explicit edit(QWidget *parent = nullptr, Empresa *empresa_ = nullptr);
    ~edit();

    void clear_LineEdits();

private slots:
    void on_bt_edit_clicked();

    void on_bt_search_clicked();

    void on_bt_exihibition_clicked();

    void att_list();

    void on_pushButton_clicked();

    void on_bt_erase_clicked();

private:
    Ui::edit *ui;
    Empresa *empresa;
    vector<QString> allLines;
    Signals* mySignals;
};

#endif // EDIT_H
