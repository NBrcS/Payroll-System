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
    edit_form = new edit(this, &empresa);
    edit_form->show();
    att_list();
}


void MainWindow::on_bt_financial_clicked()
{
    financial_form = new financial(this, &empresa);
    financial_form->show();
    att_list();

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
    final = new finaledit(this, &empresa, -1);
    final->show();
    att_list();

}

void MainWindow::att_list()
{
    QString name, designation, view;

    ui->listFuncionarios->clear();

    int size = empresa.getVectorSize();
    for(int i = 0; i < size; i++){
        QString name = QString::fromStdString(empresa.get_Func_com_index(i)->getNome());
        QString number = QString::fromStdString(empresa.get_Func_com_index(i)->getCodFuncionario());

        QString view = number + " - " + name;
        ui->listFuncionarios->addItem(view);
    }
}



