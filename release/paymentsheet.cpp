#include "paymentsheet.h"
#include "ui_paymentsheet.h"

PaymentSheet::PaymentSheet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaymentSheet)
{
    ui->setupUi(this);

    bool radio1_isToggled = ui->radio_business->isChecked();
    bool radio2_isToggled = ui->radio_employee->isChecked();

    if(radio1_isToggled || radio2_isToggled){
        ui->radio_Anual->setEnabled(true);
        ui->radio_montlhy->setEnabled(true);
    }
    else{
        ui->radio_Anual->setEnabled(false);
        ui->radio_montlhy->setEnabled(false);
    }

    QString months[] = {"",
                        "Janeiro", "Fevereiro", "Março",
                        "Abril", "Maio", "Junho",
                        "Julho", "Agosto", "Setembro",
                        "Outubro", "Novembro", "Dezembro"
                       };

    for(QString mon : months){
        ui->combo_months->addItem(mon);
    }
}

PaymentSheet::~PaymentSheet()
{
    delete ui;
}

void PaymentSheet::on_radio_employee_toggled(bool checked)
{
    if(checked){
        ui->combo_employees->setEnabled(true);
        radio1_isToggled = true;
    }
    else{
        ui->combo_employees->setEnabled(false);
        radio1_isToggled = false;
    }

    enable_AnualOrMensal();
}

void PaymentSheet::on_radio_business_toggled(bool checked)
{
    if(checked){
        radio2_isToggled = true;
    }
    else{
        radio2_isToggled = false;
    }

    enable_AnualOrMensal();

}

void PaymentSheet::enable_AnualOrMensal(){
    if(radio1_isToggled || radio2_isToggled){
        ui->radio_Anual->setEnabled(true);
        ui->radio_montlhy->setEnabled(true);
    }
    else{
        ui->radio_Anual->setEnabled(false);
        ui->radio_montlhy->setEnabled(false);
    }
}

void PaymentSheet::on_radio_montlhy_toggled(bool checked)
{
    if(checked){
        ui->combo_months->setEnabled(true);
    }
    else{
        ui->combo_months->setEnabled(false);
    }
}

