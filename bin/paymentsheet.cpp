#include "paymentsheet.h"
#include "ui_paymentsheet.h"



PaymentSheet::PaymentSheet(QWidget *parent, Empresa empresa_) :
    QDialog(parent),
    ui(new Ui::PaymentSheet)
{
    ui->setupUi(this);
    empresa = empresa_;

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

    QString monthsArr[] = {"",
                           "Janeiro", "Fevereiro", "Março",
                           "Abril", "Maio", "Junho",
                           "Julho", "Agosto", "Setembro",
                           "Outubro", "Novembro", "Dezembro"
                          };


    for(QString mon : monthsArr){
        ui->combo_months->addItem(mon);
        this->monthsVec.push_back(mon);
    }

    //comboEmployees init
    int size = this->empresa.getVectorSize();
    for(int i = 0; i < size; i++){
            QString name = QString::fromStdString(this->empresa.get_Func_com_index(i)->getNome());
            QString designation = QString::fromStdString(this->empresa.get_Func_com_index(i)->getDesignacao());

            QString view = designation  + " - " + name;
            ui->combo_employees->addItem(view);
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

void PaymentSheet::on_radio_Anual_toggled(bool checked)
{
    if(checked){
        radio3_isToggled = true;
    }
}

void PaymentSheet::on_radio_montlhy_toggled(bool checked)
{
    if(checked){
        ui->combo_months->setEnabled(true);
        radio4_isToggled = true;
    }
    else{
        ui->combo_months->setEnabled(false);
    }
}

void PaymentSheet::on_bt_calcule_clicked()
{
    double totalFinal = 0.0;
    QString out;

    ui->label_info->setText("");
    ui->label_finalValue->setText("R$");

    //business anual
    if(radio1_isToggled && radio3_isToggled){
        vector<double> valores = empresa.empresa_anual();

        out = "Relatório anual: \n\n";

        for(int i = 0; i < 12; i++){
            out += monthsVec[i] + " - R$ " + QString::number(valores[i]) + "\n";
        }
        out += "\n";

        totalFinal = valores[12];
    }
    //business mensal
    else if(radio1_isToggled && radio4_isToggled){
        int selectedMonth = ui->combo_months->currentIndex()-1;

        out = "Relatório mensal: \n\n";
        QString name, salary, designation;

        int vectorSize = this->empresa.getVectorSize();
        for(int i = 0; i < vectorSize; i++){
            name = QString::fromStdString(this->empresa.get_Func_com_index(i)->getNome());
            designation = QString::fromStdString(this->empresa.get_Func_com_index(i)->getDesignacao());
            salary = QString::number(this->empresa.get_Func_com_index(i)->getSalario());

            out += designation + ": " + name + " - R$ " + salary + "\n";
        }

        totalFinal = this->empresa.empresa_mensal(selectedMonth);
    }

    //Employee anual
    else if(radio2_isToggled && radio3_isToggled){
        QString salary, name;

        int employeeIndex = ui->combo_employees->currentIndex()-1;
        vector<double> valores = this->empresa.funcionario_anual(employeeIndex);

        name = QString::fromStdString(this->empresa.get_Func_com_index(employeeIndex)->getNome());
        out = "Relatório anual de " + name + ":\n\n";


        for(int i = 0; i < 12; i++){
            out += monthsVec[i] + " - R$ " + QString::number(valores[i]) + "\n";

        }


        totalFinal = valores[12];
    }

    //Employee mensal
    else if(radio2_isToggled && radio4_isToggled){
        QString name, sal_str, sal_daily_str, number, worked_days_str, extra_hours_str;
        int worked_days_number, extra_hours_number;
        double sal_number, sal_daily_number, hour_value;

        int employee_index = ui->combo_employees->currentIndex()-1;
        int month_index = ui->combo_months->currentIndex()-1;

        name = QString::fromStdString(this->empresa.get_Func_com_index(employee_index)->getNome());
        sal_number = this->empresa.get_Func_com_index(employee_index)->getSalario();
        sal_str = QString::number(sal_number);
        sal_daily_number = sal_number / 30;
        sal_daily_str = QString::number(sal_daily_number);
        number = QString::fromStdString(this->empresa.get_Func_com_index(employee_index)->getCodFuncionario());
        worked_days_number = this->empresa.get_Func_com_index(employee_index)->getDiasTrabalhados(month_index);
        worked_days_str = QString::number(worked_days_number);
        extra_hours_number = this->empresa.get_Func_com_index(employee_index)->getHorasExtras(month_index);
        extra_hours_str = QString::number(extra_hours_number);

        out = "Relatório mensal de " + name + ": \n\n";
        out += "Mês: " + monthsVec[month_index] + "\n";
        out += "Número: " + number + "\n";
        out += "Salário mensal: " + sal_str + "\n";
        out += "Salário diário: " + sal_daily_str + "\n";
        out += "Dias trabalhados:  " + worked_days_str + "\n";
        out += "Horas extras: " + extra_hours_str + "\n";

        hour_value = sal_daily_number / 8;
        totalFinal = (sal_daily_number * worked_days_number) + (hour_value * extra_hours_number);
    }


    QString finalString = "R$ " + QString::number(totalFinal);
    ui->label_info->setText(out);
    ui->label_finalValue->setText(finalString);
}

