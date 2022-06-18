#include "finaledit.h"

#include "diretor.h"
#include "gerente.h"
#include "operador.h"
#include "presidente.h"

#include "ui_finaledit.h"
#include <QModelIndex>
#include <ctime>

finaledit::finaledit(QWidget *parent, Empresa *empresa_, int index_) :
    QDialog(parent),
    ui(new Ui::finaledit)
{
    ui->setupUi(this);

    this->empresa = empresa_;
    this->index = index_;

    clear_all_edits();
    ui->lineEdit_Day->setValidator( new QIntValidator(0, 31, this) );
    ui->lineEdit_Mon->setValidator( new QIntValidator(0, 12, this) );
    ui->lineEdit_Year->setValidator( new QIntValidator(1940, 2100, this) );
    ui->lineEdit_Salary->setValidator( new QIntValidator(0, 100000000, this) );

    on_listWidget_infoExihibiton_currentRowChanged(index);
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

    ui->radio_President->setChecked(false);
    ui->radio_Director->setChecked(false);
    ui->radio_Operator->setChecked(false);
    ui->radio_Manager->setChecked(false);
}

void finaledit::on_bt_att_clicked()
{

    bool selected;
    if(ui->listWidget_infoExihibiton->currentRow() <= 0){
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

    bool existe = false;
    string nome_str = name.toStdString();
    for(int i = 0; i < empresa->getVectorSize(); i++)
    {
        if(nome_str.compare(empresa->get_Func_com_index(i)->getNome()) == 0 ) existe = true;
    }

    if(!existe){
        bool a = name.compare("") != 0;
        bool b = phone.compare("") != 0;
        bool c = adress.compare("") != 0;
        bool d = salary > 0;
        bool e = day > 0;
        bool f = mon > 0;
        bool g = year > 0;

        if(a && b && c && d && e && f && g ){
            empresa->add_func(funcionario);
            QMessageBox::information(this, "SUCESSO", "Funcionario adicionado com sucesso");

        }
        else QMessageBox::critical(this, "ERRO", "Existe algum parametro vazio");

    }else if(existe && selected){
        empresa->att_func(funcionario, index);
        QMessageBox::information(this, "SUCESSO", "Funcionario atualizado com sucesso");

    }else if(existe && !selected){
        QMessageBox::critical(this, "ERRO", "Este funcionário já está cadastrado no sistema");
    }

    att_list();
    clear_all_edits();
}

void finaledit::select_func(int index)
{
    ui->listWidget_infoExihibiton->setCurrentRow(index);
}

void finaledit::att_list()
{
    QString name, designation, view;

    ui->listWidget_infoExihibiton->clear();

    int size = empresa->getVectorSize();
    for(int i = 0; i < size; i++){
        name = QString::fromStdString(empresa->get_Func_com_index(i)->getNome());
        designation = QString::fromStdString(empresa->get_Func_com_index(i)->getDesignacao());

        view = name + " - " + designation;
        ui->listWidget_infoExihibiton->addItem(view);
    }
}

void finaledit::on_listWidget_infoExihibiton_currentRowChanged(int index)
{
    clear_all_edits();

    if(index >= 0)
    {
        ui->listWidget_infoExihibiton->setCurrentRow(index);
        ui->lineEdit_Name->setText( QString::fromStdString(this->empresa->get_Func_com_index(index)->getNome()));
        ui->lineEdit_PhoneNumber->setText(QString::fromStdString(this->empresa->get_Func_com_index(index)->getTelefone()));
        ui->lineEdit_Adress->setText(QString::fromStdString(this->empresa->get_Func_com_index(index)->getEndereco()));
        ui->lineEdit_Salary->setText(QString::number(this->empresa->get_Func_com_index(index)->getSalario()));
        ui->lineEdit_Day->setText(QString::number(this->empresa->get_Func_com_index(index)->getDataIngresso().tm_mday));
        ui->lineEdit_Mon->setText(QString::number(this->empresa->get_Func_com_index(index)->getDataIngresso().tm_mon));
        ui->lineEdit_Year->setText(QString::number(this->empresa->get_Func_com_index(index)->getDataIngresso().tm_year));

        string designacao = this->empresa->get_Func_com_index(index)->getDesignacao();
        if(designacao.compare("Operador") == 0){
            ui->radio_Operator->setChecked(true);
            on_radio_Operator_toggled(true);

        } else if(designacao.compare("Gerente") == 0){
            ui->radio_Manager->setChecked(true);
            on_radio_Manager_toggled(true);
            ui->lineEdit_morphy1->setText(QString::fromStdString(( (Gerente*) this->empresa->get_Func_com_index(index))->getAreaSupervisao()));

        } else if(designacao.compare("Diretor") == 0){
            ui->radio_Director->setChecked(true);
            on_radio_Director_toggled(true);
            ui->lineEdit_morphy1->setText(QString::fromStdString(( (Diretor*) this->empresa->get_Func_com_index(index))->getAreaSupervisao()));
            ui->lineEdit_morphy2->setText(QString::fromStdString(( (Diretor*) this->empresa->get_Func_com_index(index))->getAreaFormacao()));

        } else if(designacao.compare("Presidente") == 0){
            ui->radio_President->setChecked(true);
            on_radio_President_toggled(true);
            ui->lineEdit_morphy2->setText(QString::fromStdString(( (Presidente*) this->empresa->get_Func_com_index(index))->getAreaFormacao()));
            ui->lineEdit_morphy1->setText(QString::fromStdString(( (Presidente*) this->empresa->get_Func_com_index(index))->getFormacaoMaxima()));

        }
    }
}

void finaledit::clear_all_edits()
{
    ui->lineEdit_Name->setText("");
    ui->lineEdit_PhoneNumber->setText("");
    ui->lineEdit_Adress->setText("");
    ui->lineEdit_Salary->setText("");
    ui->lineEdit_Day->setText("");
    ui->lineEdit_Mon->setText("");
    ui->lineEdit_Year->setText("");
    ui->lineEdit_morphy1->setText("");
    ui->lineEdit_morphy2->setText("");

    clear_bools();
}



void finaledit::on_pushButton_clicked()
{
    clear_all_edits();
}

