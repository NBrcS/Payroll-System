#ifndef FINANCIAL_H
#define FINANCIAL_H

#include <QDialog>
#include "empresa.h"
#include "data.h"


namespace Ui {
class financial;
}

class financial : public QDialog
{
    Q_OBJECT

public:
    explicit financial(QWidget *parent = nullptr);
    ~financial();

private slots:
    void on_bt_upSalary_clicked();

    void on_bt_generatePaymentSheet_clicked();

private:
    Ui::financial *ui;

    Data *data;

};

#endif // FINANCIAL_H
