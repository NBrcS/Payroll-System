#include "mainwindow.h"

#include "diretor.h"
#include "gerente.h"
#include "operador.h"
#include "presidente.h"
#include <ctime>

#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    empresa = Empresa();







    tm data1;

    data1.tm_hour = 0;
    data1.tm_isdst = 0;
    data1.tm_min = 0;
    data1.tm_sec = 0;
    data1.tm_wday = 0;
    data1.tm_yday = 0;

    data1.tm_mday = 1;
    data1.tm_mon = 2;
    data1.tm_year = 2001;
    Funcionario* operador = new Operador("Carlos",
                                         "Logo ali",
                                         "8 999 mea mole mea dura",
                                         "Operador",
                                         data1, 2000);
    //qDebug() << "Endereco de operador: " << &operador;
    //qDebug() << "valor do operador: " << operador;
    empresa.add_func(operador);

    data1.tm_mday = 7;
    data1.tm_mon = 10;
    data1.tm_year = 2009;
    Funcionario* gerente = new Gerente("Produção",
                                       "Joao",
                                       "bem ali",
                                       "3377896",
                                       "Gerente",
                                       data1, 2000);
    //qDebug() << "Endereco de Gerente: " << &gerente;
    //qDebug() << "valor do Gerente: " << ope;
    empresa.add_func(gerente);

    data1.tm_mday = 15;
    data1.tm_mon = 4;
    data1.tm_year = 2005;
    Funcionario* diretor = new Diretor("Produção",
                                       "bacharelado",
                                       "vandui",
                                       "la nos planalto",
                                       "3377896",
                                       "Diretor",
                                       data1, 2000);
    //qDebug() << "Endereco de Diretor: " << &diretor;
    //qDebug() << "valor do Diretor: " << ope;
    empresa.add_func(diretor);

    data1.tm_mday = 11;
    data1.tm_mon = 9;
    data1.tm_year = 1999;
    Funcionario* presidente = new Presidente("Administracao",
                                             "Mestrado",
                                             "gui",
                                             "monteiro",
                                             "3377896",
                                             "Presidente",
                                             data1, 2000);
    //qDebug() << "Endereco de Presidente: " << &presidente;
    //qDebug() << "valor do Presidente: " << ope;
    empresa.add_func(presidente);




















    //credits string
    QString out[] = {"Este software foi desenvolvido pelos alunos \n\n",
                     "- Gabriel Nóbrega\n",
                     "- Lucas Soares\n",
                     "- Saulo Maranhão\n\n",
                     "Em requisição do professor Derzu Omaia, que leciona na instituição federal de ensino UFPB.\n",
                     "O código é aberto e está exibido no github https://github.com/NBrcS/Payroll-System, qualquer ",
                     "mudança que você desenvolvedor curioso ou usuário comum estiver interessado em implementar, será ",
                     "aceito um pull-request e analisado para melhor funcionameto do software\n\n",
                     "A todos os usuários que exibirem esta mensagem, agradecemos pelo feedback e pelo uso mesmo que para testes\n",
                     "Tenha um bom uso do nosso software!"
                    };

    for(QString str : out){
        feedback += str;
    }
    att_list();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bt_edit_clicked()
{
    edit_form = new edit(this, empresa);
    edit_form->show();

}


void MainWindow::on_bt_financial_clicked()
{
    financial_form = new financial(this, empresa);
    financial_form->show();
}


void MainWindow::on_bt_exit_clicked()
{
    this->close();
}


void MainWindow::on_bt_credits_clicked()
{
    QMessageBox::about(this, "Créditos", feedback);
}


void MainWindow::on_bt_add_clicked()
{
    final = new finaledit(this, empresa);
    final->show();
}

void MainWindow::att_list()
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



