#include "edit.h"
#include "ui_edit.h"
#include "finaledit.h"
#include "exihibition.h"


edit::edit(QWidget *parent, Empresa empresa_) :
    QDialog(parent),
    ui(new Ui::edit)
{
    ui->setupUi(this);
    empresa = empresa_;
    att_list();
    clear_LineEdits();
}

edit::~edit()
{
    delete ui;
}

void edit::on_bt_edit_clicked()
{
    int index;

    finaledit* final = new finaledit();
    mySignals->connect(this, SIGNAL( funcionario_selecionado( int index )), final,  SLOT( select_func( int index ) ));

    if(ui->listWidget->currentRow() == 0){
        index = 0;
    }
    else{
        index = ui->listWidget->currentRow() - 1;
    }


    emit mySignals->funcionario_selecionado(index);
    final->show();
    att_list();

}

void edit::clear_LineEdits(){
    ui->edit_name->setText("");
    ui->edit_adress->setText("");
    ui->edit_number->setText("");
    ui->edit_designation->setText("");
    ui->edit_day1->setText("");
    ui->edit_mon1->setText("");
    ui->edit_year1->setText("");
    ui->edit_day2->setText("");
    ui->edit_mon2->setText("");
    ui->edit_year2->setText("");
}

void edit::on_bt_search_clicked()
{
    allLines.push_back(ui->edit_name->text());
    allLines.push_back(ui->edit_adress->text());
    allLines.push_back(ui->edit_number->text());
    allLines.push_back(ui->edit_designation->text());
    allLines.push_back(ui->edit_day1->text());
    allLines.push_back(ui->edit_mon1->text());
    allLines.push_back(ui->edit_year1->text());
    allLines.push_back(ui->edit_day2->text());
    allLines.push_back(ui->edit_mon2->text());
    allLines.push_back(ui->edit_year2->text());

    vector<string> str_parametros;
    for(QString str : allLines){
        str_parametros.push_back(str.toStdString());
    }

    vector<int> achados = this->empresa.funcionarios_achados(str_parametros);

    ui->listWidget->clear();
    for(int index : achados){
        QString name = QString::fromStdString(empresa.get_Func_com_index(index)->getNome());
        QString number = QString::fromStdString(empresa.get_Func_com_index(index)->getCodFuncionario());

        QString view = number + " - " + name;
        ui->listWidget->addItem(view);

    }
}


void edit::on_bt_exihibition_clicked()
{
    int index;

    Exihibition* exib = new Exihibition();
    mySignals->connect(this, SIGNAL( funcionario_selecionado( int index )), exib,  SLOT( getIndex( int index_ ) ));

    if(ui->listWidget->currentRow() == 0){
        index = 0;
    }
    else{
        index = ui->listWidget->currentRow() - 1;
    }

    emit mySignals->funcionario_selecionado(index);

    exib->show();
    att_list();
}

void edit::att_list()
{
    QString name, designation, view;

    ui->listWidget->clear();

    int size = empresa.getVectorSize();
    for(int i = 0; i < size; i++){
            QString name = QString::fromStdString(empresa.get_Func_com_index(i)->getNome());
            QString number = QString::fromStdString(empresa.get_Func_com_index(i)->getCodFuncionario());

            QString view = number + " - " + name;
            ui->listWidget->addItem(view);
    }

}

void edit::receber_dados(Empresa& empresa_){
    Empresa* p_data = &empresa_;
    empresa = *p_data;
}

