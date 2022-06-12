#ifndef EXIHIBITION_H
#define EXIHIBITION_H

#include <QDialog>
#include "data.h"
#include <ctime>

namespace Ui {
class Exihibition;
}

class Exihibition : public QDialog
{
    Q_OBJECT

public:
    explicit Exihibition(QWidget *parent = nullptr, Data* data_ = nullptr);
    ~Exihibition();

    void att_exib();
    int getIndex(int);

private slots:
    void receber_dados(Data&);


private:
    Ui::Exihibition *ui;
    Data* data;
    int index;

};

#endif // EXIHIBITION_H
