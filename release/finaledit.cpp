#include "finaledit.h"
#include "ui_finaledit.h"

finaledit::finaledit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::finaledit)
{
    ui->setupUi(this);
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
}

void finaledit::clear_Morphys(){

    ui->label_morphy1->setText("");
    ui->label_morphy2->setText("");
    ui->lineEdit_morphy1->setEnabled(false);
    ui->lineEdit_morphy2->setEnabled(false);
}
