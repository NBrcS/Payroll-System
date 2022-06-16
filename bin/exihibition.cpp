#include "exihibition.h"
#include "ui_exihibition.h"

Exihibition::Exihibition(QWidget *parent, Empresa empresa_) :
    QDialog(parent),
    ui(new Ui::Exihibition)
{
    ui->setupUi(this);
    empresa = empresa_;

    att_exib();
}

Exihibition::~Exihibition()
{
    delete ui;
}

void Exihibition::att_exib(){

    QString months[] = {"Janeiro", "Fevereiro", "Março",
                        "Abril", "Maio", "Junho",
                        "Julho", "Agosto", "Setembro",
                        "Outubro", "Novembro", "Dezembro"
                        };


    //labels att
    ui->label_name->setText(QString::fromStdString(empresa.get_Func_com_index(index)->getNome()));
    ui->label_code->setText(QString::fromStdString(empresa.get_Func_com_index(index)->getCodFuncionario()));
    ui->label_phoneNumber->setText(QString::fromStdString(empresa.get_Func_com_index(index)->getTelefone()));
    ui->label_adress->setText(QString::fromStdString(empresa.get_Func_com_index(index)->getEndereco()));
    ui->label_designation->setText(QString::fromStdString(empresa.get_Func_com_index(index)->getDesignacao()));

    QString salary = "R$ " + QString::number(empresa.get_Func_com_index(index)->getSalario());
    ui->label_Salary->setText(salary);

    QString date = QString::number(empresa.get_Func_com_index(index)->getDataIngresso().tm_mday) +
                    "/" +
                   QString::number(empresa.get_Func_com_index(index)->getDataIngresso().tm_mon) +
                    "/" +
                    QString::number(empresa.get_Func_com_index(index)->getDataIngresso().tm_year);
    ui->label_date->setText(date);


    //list att
    vector<double> montlhys = empresa.funcionario_anual(index);
    QString out;

    ui->listWidget->addItem("Mensal\n\n");
    for(unsigned long long i = 0; i < montlhys.size(); i++){
        out = months[i] + " - R$ " + QString::number(montlhys[i]);
        ui->listWidget->addItem(out);
    }
}

int Exihibition::getIndex(int index_){
    return index = index_;
}

void Exihibition::receber_dados(Empresa& data_){
    Empresa* p_data = &data_;
    empresa = *p_data;
}

