#include "finaledit.h"
#include "ui_finaledit.h"
#include <QModelIndex>
#include <ctime>

finaledit::finaledit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::finaledit)
{
    ui->setupUi(this);

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
}

void finaledit::clear_Morphys(){

    ui->label_morphy1->setText("");
    ui->label_morphy2->setText("");
    ui->lineEdit_morphy1->setEnabled(false);
    ui->lineEdit_morphy2->setEnabled(false);
}

void finaledit::clear_bools(){
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
    QString code = ui->lineEdit_Code->text();
    QString phone = ui->lineEdit_PhoneNumber->text();
    QString adress = ui->lineEdit_Adress->text();
    double salary = ui->lineEdit_Salary->text().toDouble();
    QString designation = ui->lineEdit_Designation->text();
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

        funcionario = new Diretor( /* PRECISO COLOCAR OS PARAMETROS!!!  */ );
    }
    else if(president){
        QString academicFormation = ui->lineEdit_morphy2->text();
        QString degreeArea =  ui->lineEdit_morphy1->text();

        funcionario = new Presidente( /* PRECISO COLOCAR OS PARAMETROS!!!  */ );
    }
    else if(manager){
        QString supervision = ui->lineEdit_morphy1->text();

        funcionario = new Gerente( /* PRECISO COLOCAR OS PARAMETROS!!!  */ );
    }
    else if(operador){
        funcionario = new Operador( /* PRECISO COLOCAR OS PARAMETROS!!!  */ );
    }


    if(selected == false){
        data->getEmpresa().add_func(funcionario);
    }
    else{
        int index = ui->listWidget_infoExihibiton->currentRow() - 1;
        data->getEmpresa().att_func(funcionario, index);
    }
    att_list();
}

void finaledit::select_func(int index){
    ui->listWidget_infoExihibiton->setCurrentRow(index);
}

void finaledit::att_list(){
    QString name, designation, view;

    ui->listWidget_infoExihibiton->addItem("");
    int size = data->getEmpresa().getVectorSize();
    for(int i = 0; i < size; i++){
            name = data->getEmpresa().get_Func_com_index(i).getNome();
            designation = data->getEmpresa().get_Func_com_index(i).getDesignacao();

            view = designation  + " - " + name;
            ui->listWidget_infoExihibiton->addItem(view);
    }
}




