#ifndef DIRETOR_H
#define DIRETOR_H

#include "funcionario.h"

class Diretor : public Funcionario{

    public:

        Diretor();
        Diretor(string areaSupervisao, string areaFormacao, string codFuncionario, string nome, string endereco, string telefone, string designacao, tm dataIngresso, double salario);
        virtual ~Diretor(){}

        void setAreaSupervisao(string areaSupervisao);
        void setAreaFormacao(string areaFormacao);
        string getAreaSupervisao();
        string getAreaFormacao();

        void aumentoSalarial();
    private:

        string areaSupervisao;
        string areaFormacao;
};

#endif // DIRETOR_H
