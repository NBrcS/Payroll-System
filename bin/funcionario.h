#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <iostream>
#include <string>

using namespace std;

class Funcionario{

    public:
        Funcionario(int = 0);
        explicit Funcionario(string nome, string endereco, string telefone, string designacao, tm dataIngresso, double salario);
        virtual ~Funcionario(){}

        void setCodFuncionario(string CodFuncionario);
        void setNome(string nome);
        void setEndereco(string endereco);
        void setTelefone(string telefone);
        void setDesignacao(string designacao);
        void setDataIngresso(tm dataIngresso);
        void setSalario(double salario);
        void setSalario_tributado(double newSalario_tributado);
        void setValor_hora(double newValor_hora);
        void setDiasTrabalhados(int dias, int index);
        void setHoras_trabalhadas(int horas, int index);
        void setSalario_mensal(double salario, int index);
        string getCodFuncionario();
        string getNome();
        string getEndereco();
        string getTelefone();
        string getDesignacao();
        tm getDataIngresso();
        double getSalario();      
        double getSalario_tributado() const;
        double getValor_hora() const;

        bool ComparaDatas(tm data);
        void tributarSalario();
        double get_SalarioMes(int index);
        int getDiasTrabalhados(int index);
        int getHorasExtras(int index);

        virtual void aumentoSalarial() = 0;

protected:
        string codFuncionario;
        string nome;
        string endereco;
        string telefone;
        string designacao;
        tm dataIngresso;
        double salario;
        double salario_tributado;
        double valor_hora;

        int horasTrabalhadas[12];
        int diasTrabalhados[12];
        double salariosMensais[12];
};


#endif // FUNCIONARIO_H
