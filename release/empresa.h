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

        void adicionarFuncionario(Funcionario*);
        void editarFuncionario();
        void excluirFuncionario();
        void exibirFuncionario();
        void exibirListaFuncionarios();
        void exibirListaFuncionarios_tipo();
        void aumentoSalarioGeral();
        void calcularFolhaSalarial();
        void imprimirFolhaSalarial_Funcionario();
        void imprimirFolhaSalarial_Empresa();
        void buscarFuncionario();

        int getVectorSize();
        Funcionario* get_Func_com_index(int);
        vector<double> empresa_anual();
        double empresa_mensal(int);
        vector<double> funcionario_anual(int);
        double funcionario_mensal(int, int);
        vector<int> funcionarios_achados(vector<string>);
        bool compare_datas(tm, tm);
};

#endif
