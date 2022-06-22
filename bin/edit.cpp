#include "edit.h"
#include "ui_edit.h"
#include "finaledit.h"
#include "exihibition.h"
#include <QtSql>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include "funcionario.h"


edit::edit(QWidget *parent, Empresa *empresa_) :
    QDialog(parent),
    ui(new Ui::edit)
{
    ui->setupUi(this);

    empresa = empresa_;

    ui->edit_day1->setValidator( new QIntValidator(0, 31, this) );
    ui->edit_mon1->setValidator( new QIntValidator(0, 12, this) );
    ui->edit_year1->setValidator( new QIntValidator(1940, 2100, this) );
    ui->edit_day2->setValidator( new QIntValidator(0, 31, this) );
    ui->edit_mon2->setValidator( new QIntValidator(0, 12, this) );
    ui->edit_year2->setValidator( new QIntValidator(1940, 2100, this) );

    att_list();
    clear_LineEdits();

   QSqlQuery query;
    query.prepare("select * from tb_funcionario");
    if(query.exec()){
        //int cont = 0;

       /* ui->listWidget->setColumnCount(10);
            while(query.next()){
                ui->listWidget->insertRow(cont);
                ui->listWidget->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
                ui->listWidget->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
                ui->listWidget->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
                ui->listWidget->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
                ui->listWidget->setItem(cont,4,new QTableWidgetItem(query.value(4).toString()));
                ui->listWidget->setItem(cont,5,new QTableWidgetItem(query.value(5).toString()));
                ui->listWidget->setItem(cont,6,new QTableWidgetItem(query.value(6).toString()));
                ui->listWidget->setItem(cont,7,new QTableWidgetItem(query.value(7).toString()));
                ui->listWidget->setItem(cont,8,new QTableWidgetItem(query.value(8).toString()));
                ui->listWidget->setItem(cont,9,new QTableWidgetItem(query.value(9).toString()));
                ui->listWidget->setRowHeight(cont,20);
                cont++;
             */ }
            else{
        //QMessageBox::warning(this,"ERRO","Erro ao pesquisar tabela de contatos");

 }





}

edit::~edit()
{
    delete ui;
}

void edit::on_bt_edit_clicked()
{
    int index;
    index = ui->listWidget->currentRow();

    if(index < 0)
    {
        QMessageBox::critical(this, "ERRO", "Nenhum funcionario selecionado");
        return;
    }
    else
    {
        finaledit* final = new finaledit(this, empresa, index);
        final->show();
    }

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
    if(ui->edit_name->text() != "") allLines.push_back(ui->edit_name->text());
    else allLines.push_back("");

    if(ui->edit_adress->text() != "") allLines.push_back(ui->edit_adress->text());
    else allLines.push_back("");

    if(ui->edit_number->text() != "") allLines.push_back(ui->edit_number->text());
    else allLines.push_back("");

    if(ui->edit_designation->text() != "") allLines.push_back(ui->edit_designation->text());
    else allLines.push_back("");

    if(ui->edit_day1->text() != "") allLines.push_back(ui->edit_day1->text());
    else allLines.push_back("");

    if(ui->edit_mon1->text() != "") allLines.push_back(ui->edit_mon1->text());
    else allLines.push_back("");

    if(ui->edit_year1->text() != "") allLines.push_back(ui->edit_year1->text());
    else allLines.push_back("");

    if(ui->edit_day2->text() != "") allLines.push_back(ui->edit_day2->text());
    else allLines.push_back("");

    if(ui->edit_mon2->text() != "") allLines.push_back(ui->edit_mon2->text());
    else allLines.push_back("");

    if(ui->edit_year2->text() != "") allLines.push_back(ui->edit_year2->text());
    else allLines.push_back("");



    vector<string> str_parametros;
    for(const QString &str : allLines){
        str_parametros.push_back(str.toStdString());
    }

    try {
        vector<int> achados = this->empresa->funcionarios_achados(str_parametros);
        ui->listWidget->clear();
        for(int index : achados){
            QString name = QString::fromStdString(empresa->get_Func_com_index(index)->getNome());
            QString number = QString::fromStdString(empresa->get_Func_com_index(index)->getCodFuncionario());

            QString view = number + " - " + name;
            ui->listWidget->addItem(view);
        }
    } catch (string e) {
        QMessageBox::critical(this, "ERRO", QString::fromStdString(e));
    }

    allLines.clear();



}


void edit::on_bt_exihibition_clicked()
{
    if(ui->listWidget->currentRow() < 0){
        QMessageBox::critical(this, "ERRO", "Nenhum funcionario selecionado");
    }
    else{
        int index;
        index = ui->listWidget->currentRow();

        Exihibition* exib = new Exihibition(this, empresa, index);
        exib->show();
        att_list();
    }
}

void edit::att_list()
{
    QString name, designation, view;

    ui->listWidget->clear();

    int size = empresa->getVectorSize();
    for(int i = 0; i < size; i++){
            QString name = QString::fromStdString(empresa->get_Func_com_index(i)->getNome());
            QString number = QString::fromStdString(empresa->get_Func_com_index(i)->getCodFuncionario());

            QString view = number + " - " + name;
            ui->listWidget->addItem(view);
    }
}

void edit::on_pushButton_clicked()
{
    clear_LineEdits();
    att_list();
}


void edit::on_bt_erase_clicked()
{
    int index = ui->listWidget->currentRow();

    if(index < 0)
    {
        QMessageBox::critical(this, "ERRO", "Nenhum funcionario selecionado");
        return;
    }
    else
    {
        empresa->apagar_funcionario(index);
        QMessageBox::information(this, "DELETAR", "O fucionario foi apagado com sucesso do sistema!");
    }
    att_list();
}

