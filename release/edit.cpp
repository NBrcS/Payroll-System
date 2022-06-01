#include "edit.h"
#include "ui_edit.h"
#include "finaledit.h"

edit::edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit)
{
    ui->setupUi(this);
}

edit::~edit()
{
    delete ui;
}

void edit::on_bt_edit_clicked()
{
    finaledit final;
    final.setModal(true);
    final.exec();
}

