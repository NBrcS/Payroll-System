#ifndef OPERADOR_H
#define OPERADOR_H

#include "funcionario.h"

class Operador : public Funcionario{

    public:

        Operador();
        Operador(string codFuncionario, string nome, string endereco, string telefone, string designacao, tm dataIngresso, double salario);
        virtual ~Operador(){}

        void aumentoSalarial();
};


#endif // OPERADOR_H
