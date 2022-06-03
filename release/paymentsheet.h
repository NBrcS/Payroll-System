#ifndef PAYMENTSHEET_H
#define PAYMENTSHEET_H

#include <QDialog>
#include "data.h"

namespace Ui {
class PaymentSheet;
}

class PaymentSheet : public QDialog
{
    Q_OBJECT

public:
    explicit PaymentSheet(QWidget *parent = nullptr);
    ~PaymentSheet();

private slots:
    void on_radio_employee_toggled(bool checked);

    void on_radio_business_toggled(bool checked);

    void enable_AnualOrMensal();

    void on_radio_montlhy_toggled(bool checked);

    void on_radio_Anual_toggled(bool checked);

    void on_bt_calcule_clicked();

private:
    Ui::PaymentSheet *ui;
    bool radio1_isToggled;
    bool radio2_isToggled;
    bool radio3_isToggled;
    bool radio4_isToggled;

    vector<QString> monthsVec;
    Data* data;
};

#endif // PAYMENTSHEET_H
