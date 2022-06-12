#ifndef FINANCIAL_H
#define FINANCIAL_H

#include <QDialog>
#include "empresa.h"
#include "data.h"
#include "paymentsheet.h"
#include <QMessageBox>



namespace Ui {
class financial;
}

class financial : public QDialog
{
    Q_OBJECT

public:
    explicit financial(QWidget *parent = nullptr, Data* data_ = nullptr);
    ~financial();

private slots:
    void on_bt_upSalary_clicked();

    void on_bt_generatePaymentSheet_clicked();

    void receber_dados(Data&);

private:
    Ui::financial *ui;
    PaymentSheet* sheet;

    Data *data;

};

#endif // FINANCIAL_H
