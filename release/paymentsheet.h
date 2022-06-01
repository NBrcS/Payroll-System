#ifndef PAYMENTSHEET_H
#define PAYMENTSHEET_H

#include <QDialog>

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

private:
    Ui::PaymentSheet *ui;
    bool radio1_isToggled;
    bool radio2_isToggled;
};

#endif // PAYMENTSHEET_H
