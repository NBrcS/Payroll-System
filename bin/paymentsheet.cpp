#include "paymentsheet.h"
#include "ui_paymentsheet.h"

PaymentSheet::PaymentSheet(QWidget *parent, Empresa* empresa_) :
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
    int size = this->empresa->getVectorSize();
    for(int i = 0; i < size; i++){
        QString name = QString::fromStdString(this->empresa->get_Func_com_index(i)->getNome());
        QString designation = QString::fromStdString(this->empresa->get_Func_com_index(i)->getDesignacao());

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
    radio1_isToggled = false;

    if(checked){
        ui->combo_employees->setEnabled(true);
        radio2_isToggled = true;
    }
    else{
        ui->combo_employees->setEnabled(false);
        radio2_isToggled = false;
    }

    enable_AnualOrMensal();
}

void PaymentSheet::on_radio_business_toggled(bool checked)
{
    radio2_isToggled = false;

    if(checked){
        radio1_isToggled = true;
    }
    else{
        radio1_isToggled = false;
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
    radio4_isToggled = false;

    if(checked){
        radio3_isToggled = true;
    }
}

void PaymentSheet::on_radio_montlhy_toggled(bool checked)
{
    radio3_isToggled = false;

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
    QString out = "";

    ui->label_info->setText("");
    ui->label_finalValue->setText("R$");

    //business anual
    if(radio1_isToggled && radio3_isToggled){
        vector<double> valores = empresa->empresa_anual();

        for(int i = 0; i < 12; i++){
            out += monthsVec[i+1] + " - R$ " + QString::number(valores[i]) + "\n";
        }
        out += "\n";

        totalFinal = valores[12];
    }
    //business mensal
    else if(radio1_isToggled && radio4_isToggled){
        int selectedMonth = ui->combo_months->currentIndex()-1;

        out = "Relatório mensal: \n\n";
        QString name, salary, designation;

        int vectorSize = this->empresa->getVectorSize();
        for(int i = 0; i < vectorSize; i++){
            name = QString::fromStdString(this->empresa->get_Func_com_index(i)->getNome());
            designation = QString::fromStdString(this->empresa->get_Func_com_index(i)->getDesignacao());
            salary = QString::number(this->empresa->get_Func_com_index(i)->get_SalarioMes(selectedMonth));

            out += (designation + ": " + name + " - R$ " + salary + "\n");
        }

        totalFinal = this->empresa->empresa_mensal(selectedMonth);
    }

    //Employee anual
    else if(radio2_isToggled && radio3_isToggled){
        QString salary, name;

        int employeeIndex = ui->combo_employees->currentIndex();
        vector<double> valores = this->empresa->funcionario_anual(employeeIndex);

        name = QString::fromStdString(this->empresa->get_Func_com_index(employeeIndex)->getNome());
        for(int i = 0; i < 12; i++){
            out += monthsVec[i+1] + " - R$ " + QString::number(valores[i]) + "\n";

        }
        totalFinal = valores[12];
    }

    //Employee mensal
    else if(radio2_isToggled && radio4_isToggled){
        QString name, number, sal_str_brt, sal_str_liq , sal_daily_str, worked_days_str, extra_hours_str;

        int index_funcionario = ui->combo_employees->currentIndex();
        int index_mes = ui->combo_months->currentIndex();

        name = QString::fromStdString(this->empresa->get_Func_com_index(index_funcionario)->getNome());
        number = QString::fromStdString(this->empresa->get_Func_com_index(index_funcionario)->getCodFuncionario());
        sal_str_brt = QString::number(this->empresa->get_Func_com_index(index_funcionario)->getSalario());
        sal_str_liq = QString::number(this->empresa->get_Func_com_index(index_funcionario)->getSalario_tributado());
        sal_daily_str = QString::number(this->empresa->get_Func_com_index(index_funcionario)->getSalario_tributado() / 21);
        worked_days_str = QString::number(this->empresa->get_Func_com_index(index_funcionario)->getDiasTrabalhados(index_mes));
        extra_hours_str = QString::number(this->empresa->get_Func_com_index(index_funcionario)->getHorasExtras(index_mes));

        out = "Relatório mensal de " + name + ": \n\n";
        out += "Mês: " + monthsVec[index_mes] + "\n";
        out += "Número: " + number + "\n";
        out += "Salário mensal bruto: " + sal_str_brt + "\n";
        out += "Salário mensal liquido: " + sal_str_liq + "\n";
        out += "Salário diário liquido: " + sal_daily_str + "\n";
        out += "Dias trabalhados:  " + worked_days_str + "\n";
        out += "Horas extras: " + extra_hours_str + "\n";


        double hour_value = this->empresa->get_Func_com_index(index_funcionario)->getValor_hora();
        int worked_days = this->empresa->get_Func_com_index(index_funcionario)->getDiasTrabalhados(index_mes);
        int extra_hours = this->empresa->get_Func_com_index(index_funcionario)->getHorasExtras(index_mes);

        totalFinal = (hour_value * 8) * worked_days
                    + (hour_value * 1.5) * extra_hours;
    }


    QString finalString = "R$ " + QString::number(totalFinal);
    ui->label_info->setText(out);
    ui->label_finalValue->setText(finalString);

    out = "";
    finalString = "";
}

