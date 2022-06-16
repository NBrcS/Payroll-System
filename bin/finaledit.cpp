#include "finaledit.h"

#include "diretor.h"
#include "gerente.h"
#include "operador.h"
#include "presidente.h"

#include "ui_finaledit.h"
#include <QModelIndex>
#include <ctime>

finaledit::finaledit(QWidget *parent, Empresa empresa_) :
    QDialog(parent),
    ui(new Ui::finaledit)
{
    ui->setupUi(this);

    empresa = empresa_;

    ui->listWidget_infoExihibiton->addItem("teste");


    ui->lineEdit_Name->setText("José Bonifácio");
    ui->lineEdit_PhoneNumber->setText("(87) 9.9972-0857");
    ui->lineEdit_Adress->setText("rua Dom José Pereira Alves");
    ui->lineEdit_Salary->setText("1000");
    ui->lineEdit_Day->setText("02");
    ui->lineEdit_Mon->setText("10");
    ui->lineEdit_Year->setText("2002");


    ui->radio_Operator->setChecked(true);
    att_list();
}

finaledit::~finaledit()
{
    delete ui;
}

void finaledit::on_radio_Operator_toggled(bool checked)
{

    if(checked){
        clear_Morphys();
    }

    clear_bools();
    this->operador = true;
    this->designation = "Operador";
}

void finaledit::on_radio_Manager_toggled(bool checked)
{

    if(checked){
        clear_Morphys();

        ui->lineEdit_morphy1->setEnabled(true);
        ui->label_morphy1->setText("Área de supervisão");
    }

    clear_bools();
    this->manager = true;
    this->designation = "Gerente";
}


void finaledit::on_radio_Director_toggled(bool checked)
{

    if(checked){
        clear_Morphys();

        ui->lineEdit_morphy1->setEnabled(true);
        ui->label_morphy1->setText("Área de supervisão");
        ui->lineEdit_morphy2->setEnabled(true);
        ui->label_morphy2->setText("Área de Formação");
    }

    clear_bools();
    this->director = true;
    this->designation = "Diretor";
}

void finaledit::on_radio_President_toggled(bool checked)
{

    if(checked){
        clear_Morphys();

        ui->lineEdit_morphy1->setEnabled(true);
        ui->label_morphy1->setText("Área de Formação");
        ui->lineEdit_morphy2->setEnabled(true);
        ui->label_morphy2->setText("Formação Acadêmica");
    }

    clear_bools();
    this->president = true;
    this->designation = "Presidente";
}

void finaledit::clear_Morphys()
{

    ui->label_morphy1->setText("");
    ui->label_morphy2->setText("");
    ui->lineEdit_morphy1->setEnabled(false);
    ui->lineEdit_morphy2->setEnabled(false);
}

void finaledit::clear_bools()
{
    president = false;
    director = false;
    manager = false;
    operador = false;
}

void finaledit::on_bt_att_clicked()
{

    bool selected;
    if(ui->listWidget_infoExihibiton->currentRow() == 0){
        selected = false;
    }
    else{
        selected = true;
    }

    Funcionario* funcionario;

    QString name = ui->lineEdit_Name->text();
    QString phone = ui->lineEdit_PhoneNumber->text();
    QString adress = ui->lineEdit_Adress->text();
    double salary = ui->lineEdit_Salary->text().toDouble();
    int day = ui->lineEdit_Day->text().toInt();
    int mon = ui->lineEdit_Mon->text().toInt();
    int year = ui->lineEdit_Year->text().toInt();

    tm date;
    date.tm_mday = day;
    date.tm_mon = mon;
    date.tm_year = year;

    if(director){
        QString supervision = ui->lineEdit_morphy1->text();
        QString degreeArea =  ui->lineEdit_morphy2->text();

        funcionario = new Diretor( supervision.toStdString(),
                                   degreeArea.toStdString(),
                                   name.toStdString(),
                                   adress.toStdString(),
                                   phone.toStdString(),
                                   designation.toStdString(),
                                   date, salary);
    }
    else if(president){
        QString academicFormation = ui->lineEdit_morphy2->text();
        QString degreeArea =  ui->lineEdit_morphy1->text();

        funcionario = new Presidente( degreeArea.toStdString(),
                                      academicFormation.toStdString(),
                                      name.toStdString(),
                                      adress.toStdString(),
                                      phone.toStdString(),
                                      designation.toStdString(),
                                      date,  salary);
    }
    else if(manager){
        QString supervision = ui->lineEdit_morphy1->text();

        funcionario = new Gerente( supervision.toStdString(),
                                   name.toStdString(),
                                   adress.toStdString(),
                                   phone.toStdString(),
                                   designation.toStdString(),
                                   date,  salary);
    }
    else if(operador){
        funcionario = new Operador( name.toStdString(),
                                    adress.toStdString(),
                                    phone.toStdString(),
                                    designation.toStdString(),
                                    date,  salary);
    }


    if(selected == false){
        empresa.add_func(funcionario);
    }
    else{
        int index = ui->listWidget_infoExihibiton->currentRow() - 1;
        empresa.att_func(funcionario, index);
    }
    att_list();

    ui->lineEdit_Name->setText("");
    ui->lineEdit_PhoneNumber->setText("");
    ui->lineEdit_Adress->setText("");
    ui->lineEdit_Salary->setText("");
    ui->lineEdit_Day->setText("");
    ui->lineEdit_Mon->setText("");
    ui->lineEdit_Year->setText("");
    ui->lineEdit_morphy1->setText("");
    ui->lineEdit_morphy2->setText("");
}

void finaledit::select_func(int index)
{
    ui->listWidget_infoExihibiton->setCurrentRow(index);
}

void finaledit::att_list()
{
    QString name, designation, view;

    ui->listWidget_infoExihibiton->clear();

    int size = empresa.getVectorSize();
    for(int i = 0; i < size; i++){
            name = QString::fromStdString(empresa.get_Func_com_index(i)->getNome());
            designation = QString::fromStdString(empresa.get_Func_com_index(i)->getDesignacao());

            view = designation  + " - " + name;
            ui->listWidget_infoExihibiton->addItem(view);
    }
}


void finaledit::receber_dados(Empresa& data_)
{
    Empresa *p_data = &data_;
    empresa = *p_data;
}




