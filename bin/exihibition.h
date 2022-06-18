#ifndef EXIHIBITION_H
#define EXIHIBITION_H

#include <QDialog>
#include "empresa.h"
#include <ctime>

namespace Ui {
class Exihibition;
}

class Exihibition : public QDialog
{
    Q_OBJECT

public:
    explicit Exihibition(QWidget *parent = nullptr, Empresa* Empresa_ = nullptr, int index = 0);
    ~Exihibition();

    void att_exib();
    int getIndex(int);


private:
    Ui::Exihibition *ui;
    Empresa *empresa;
    int index;

};

#endif // EXIHIBITION_H
