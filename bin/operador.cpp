#include "operador.h"

Operador::Operador() : Funcionario(1){

}
Operador::Operador(string codFuncionario, string nome, string endereco, string telefone, string designacao, tm dataIngresso, double salario)
    : Funcionario(codFuncionario, nome, endereco, telefone, designacao, dataIngresso, salario){

}
void Operador::aumentoSalarial(){
    this->salario = this->salario + (salario * (5/100));
    this->tributarSalario();
}
