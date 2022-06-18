#include "financial.h"
#include "ui_financial.h"

financial::financial(QWidget *parent, Empresa *empresa_) :
    QDialog(parent),
    ui(new Ui::financial)
{
    ui->setupUi(this);
    empresa = empresa_;

    //listWidget init
    att_list();
}

financial::~financial()
{
    delete ui;
}

void financial::on_bt_upSalary_clicked()
{
    QString out1 = "O salário de todos os funcionários vai ser aumentado nas seguintes proporções: \n\n";
    QString out2 = "-> Operador: 5\%\n";
    QString out3 = "-> Gerente: 10\%\n";
    QString out4 = "-> Diretor: 20\%\n";
    QString out5 = "-> Presidente 30\%\n\n";
    QString out6 = "Deseja continuar?";

    QString out = out1 + out2 + out3 + out4 + out5 + out6;


    QMessageBox::StandardButton reply = QMessageBox::question(this, "Aumento Salarial", out,
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        this->empresa->aumentoSalarioGeral();
    }


}

void financial::on_bt_generatePaymentSheet_clicked()
{
    sheet = new PaymentSheet(this, empresa);
    sheet->show();
}



void financial::att_list()
{
    QString name, designation, view;

    ui->list_nameAndWork->clear();

    int size = empresa->getVectorSize();
    for(int i = 0; i < size; i++){
            QString name = QString::fromStdString(empresa->get_Func_com_index(i)->getNome());
            QString designation = QString::fromStdString(empresa->get_Func_com_index(i)->getDesignacao());

            QString view = designation  + " - " + name;
            ui->list_nameAndWork->addItem(view);
    }

}


