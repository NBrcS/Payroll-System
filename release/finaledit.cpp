#include "finaledit.h"
#include "ui_finaledit.h"

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

void finaledit::on_radio_Manager_toggled(bool checked)
{
    clear_Morphys();

    if(checked){
        ui->lineEdit_morphy1->setEnabled(true);
        ui->label_morphy1->setText("Área de supervisão");
    }

    clear_bools();
    this->manager = true;
}


void finaledit::on_radio_Director_toggled(bool checked)
{
    clear_Morphys();

    if(checked){
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
    clear_Morphys();

    if(checked){
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
}

void finaledit::on_bt_att_clicked()
{
    vector<QString> info;

    info.push_back(ui->label_Name->text());
    info.push_back(ui->label_Code->text());
    info.push_back(ui->label_PhoneNumber->text());
    info.push_back(ui->label_Adress->text());
    info.push_back(ui->label_Salary->text());
    info.push_back(ui->label_Designation->text());

    if(director){

    }






    att_list();
}

void finaledit::select_func(int index){
    QModelIndex QIndex = QString::number(index);

    ui->listWidget_infoExihibiton->setCurrentIndex(QIndex);
}

void finaledit::att_list(){
    int size = data->getEmpresa().getVectorSize();
    for(int i = 0; i < size; i++){
            QString name = data->getEmpresa().get_Func_com_index(i).getNome();
            QString designation = data->getEmpresa().get_Func_com_index(i).getDesignacao();

            QString view = designation  + " - " + name;
            ui->listWidget_infoExihibiton->addItem(view);
    }
}

