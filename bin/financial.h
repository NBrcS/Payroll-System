#ifndef FINANCIAL_H
#define FINANCIAL_H

#include <QDialog>
#include "empresa.h"
#include "empresa.h"
#include "paymentsheet.h"
#include <QMessageBox>



namespace Ui {
class financial;
}

class financial : public QDialog
{
    Q_OBJECT

public:
    explicit financial(QWidget *parent = nullptr, Empresa* empresa_ = nullptr);
    ~financial();

private slots:
    void on_bt_upSalary_clicked();

    void on_bt_generatePaymentSheet_clicked();

    void att_list();

private:
    Ui::financial *ui;
    PaymentSheet* sheet;

    Empresa* empresa;

};

#endif // FINANCIAL_H
