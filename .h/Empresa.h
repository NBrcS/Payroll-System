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
        Empresa(){}
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
}

#endif