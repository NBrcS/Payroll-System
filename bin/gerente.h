#ifndef GERENTE_H
#define GERENTE_H

#include "funcionario.h"

class Gerente : public Funcionario{

    public:
        Gerente();
        Gerente(string areaSupervisao, string codFuncionario, string nome, string endereco, string telefone, string designacao, tm dataIngresso, double salario);
        virtual ~Gerente(){}

        void setAreaSupervisao(string AreaSupervisao);
        string getAreaSupervisao();

           void aumentoSalarial();
    private:
        string areaSupervisao;

};
#endif // GERENTE_H
