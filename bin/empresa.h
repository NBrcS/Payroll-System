#ifndef EMPRESA_H
#define EMPRESA_H

#include <QVector>
#include <iostream>
#include "funcionario.h"
#include <exception>

#include "operador.h"
#include "gerente.h"
#include "diretor.h"
#include "presidente.h"

#include <iomanip>
#include <vector>
#include <ctime>
#include <string>
#include <iostream>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>


using namespace std;

class Empresa
{
    private:
        QVector<Funcionario*> funcionarios;
        double folhaSalarial[12];

    public:
        Empresa();
        virtual ~Empresa();

        int getVectorSize();
        Funcionario* get_Func_com_index(int);
        vector<double> empresa_anual();
        double empresa_mensal(int);
        vector<double> funcionario_anual(int);
        double funcionario_mensal(int, int);
        vector<int> funcionarios_achados(vector<string>);
        bool compare_datas(tm, tm);
        void add_func(Funcionario*);
        void att_func(Funcionario*, int);
        void aumentoSalarioGeral();
        void apagar_funcionario(int);
};

#endif
