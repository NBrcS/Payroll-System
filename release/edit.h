#ifndef EDIT_H
#define EDIT_H

#include <QDialog>
#include "data.h"
#include "signals.h"

namespace Ui {
class edit;
}

class edit : public QDialog
{
    Q_OBJECT

public:
    explicit edit(QWidget *parent = nullptr);
    ~edit();

    void clear_LineEdits();

private slots:
    void on_bt_edit_clicked();

    void on_bt_search_clicked();

    void on_bt_exihibition_clicked();

private:
    Ui::edit *ui;
    Data* data;
    vector<QString> allLines;
    Signals* mySignals;
};

#endif // EDIT_H
