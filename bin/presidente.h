#ifndef PRESIDENTE_H
#define PRESIDENTE_H

#include "funcionario.h"

class Presidente : public Funcionario{

    public:

        Presidente();
        Presidente(string areaFormacao, string formacaoMaxima, string codFuncionario, string nome, string endereco, string telefone, string designacao, tm dataIngresso, double salario);
        virtual ~Presidente(){}

        void setAreaFormacao(string AreaFormacao);
        void setFormacaoMaxima(string formacaoMaxima);
        string getAreaFormacao();
        string getFormacaoMaxima();

        void aumentoSalarial();
    private:

        string areaFormacao;
        string formacaoMaxima;
};

#endif // PRESIDENTE_H
