#ifndef EMPRESA_H
#define EMPRESA_H

#include <vector>
#include <iostream>
using namespace std;

class Empresa
{
    private:
        vector<Funcionario*> funcionarios;
        double folhaSalarial[12];

    public:
        Empresa();
        ~Empresa(){}

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
};

#endif
