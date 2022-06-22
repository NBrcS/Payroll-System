#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "edit.h"
#include "financial.h"
#include "data.h"
#include "finaledit.h"
#include "signals.h"
#include <QMessageBox>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bt_edit_clicked();

    void on_bt_financial_clicked();

    void on_bt_exit_clicked();

    void on_bt_credits_clicked();

    void on_bt_add_clicked();

    void att_list();

private:
    Ui::MainWindow *ui;
    edit *edit_form;
    financial* financial_form;
    finaledit* final;

    QString feedback;
    Empresa empresa;
    Signals *mySignal;
};
#endif // MAINWINDOW_H
