#include "exihibition.h"
#include "ui_exihibition.h"

Exihibition::Exihibition(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Exihibition)
{
    ui->setupUi(this);
}

Exihibition::~Exihibition()
{
    delete ui;
}

void Exihibition::att_exib(int index){

    QString months[] = {"Janeiro", "Fevereiro", "Março",
                        "Abril", "Maio", "Junho",
                        "Julho", "Agosto", "Setembro",
                        "Outubro", "Novembro", "Dezembro"
                        };


    //labels att
    ui->label_name->setText(data->getEmpresa().get_Func_com_index(index)->getNome());
    ui->label_code->setText(data->getEmpresa().get_Func_com_index(index)->getCodFuncionario());
    ui->label_phoneNumber->setText(data->getEmpresa().get_Func_com_index(index)->getTelefone());
    ui->label_adress->setText(data->getEmpresa().get_Func_com_index(index)->getEndereco());
    ui->label_designation->setText(data->getEmpresa().get_Func_com_index(index)->getDesignacao());

    QString salary = "R$ " + data->getEmpresa().get_Func_com_index(index)->getSalario();
    ui->label_Salary->setText(salary);

    QString date = data->getEmpresa().get_Func_com_index(index)->getDataIngresso().mday +
                    "/" +
                   data->getEmpresa().get_Func_com_index(index)->getDataIngresso().mon +
                    "/" +
                    data->getEmpresa().get_Func_com_index(index)->getDataIngresso().year;
    ui->label_date->setText(date);


    //list att
    vector<double> montlhys = data->getEmpresa().funcionario_anual(index);
    QString out;

    ui->listWidget->addItem("Mensal\n\n");
    for(unsigned long long i = 0; i < montlhys.size(); i++){
        out = months[i] + " - R$ " + QString::number(montlhys[i]);
        ui->listWidget->addItem(out);
    }
}
