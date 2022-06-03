#include "financial.h"
#include "ui_financial.h"
#include "paymentsheet.h"
#include <qmessagebox.h>

financial::financial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::financial)
{
    ui->setupUi(this);
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
        this->data->getEmpresa().aumentoSalarioGeral();
    }

    //listWidget init
    int size = data->getEmpresa().getVectorSize();
    for(int i = 0; i < size; i++){
            QString name = data->getEmpresa().get_Func_com_index(i).getNome();
            QString designation = data->getEmpresa().get_Func_com_index(i).getDesignacao();

            QString view = designation  + " - " + name;
            ui->list_nameAndWork->addItem(view);
    }

}

void financial::on_bt_generatePaymentSheet_clicked()
{
    PaymentSheet sheet;
    sheet.setModal(true);
    sheet.exec();
}


