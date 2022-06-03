#ifndef FINALEDIT_H
#define FINALEDIT_H

#include <QDialog>
#include "empresa.h"


namespace Ui {
class finaledit;
}

class finaledit : public QDialog
{
    Q_OBJECT

public:
    explicit finaledit(QWidget *parent = nullptr);
    ~finaledit();

private slots:
    void on_radio_Manager_toggled(bool checked);

    void on_radio_Director_toggled(bool checked);

    void on_radio_President_toggled(bool checked);

    void clear_Morphys();

private:
    Ui::finaledit *ui;
};

#endif // FINALEDIT_H
