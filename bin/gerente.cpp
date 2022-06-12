#include "gerente.h"

Gerente::Gerente() : Funcionario(2){

}
Gerente::Gerente(string areaSupervisao, string codFuncionario, string nome, string endereco, string telefone, string designacao, tm dataIngresso, double salario)
    : Funcionario(codFuncionario, nome, endereco, telefone, designacao, dataIngresso, salario){
    this->areaSupervisao = areaSupervisao;
}
void Gerente::setAreaSupervisao(string areaSupervisao){
    this->areaSupervisao = areaSupervisao;
}
string Gerente::getAreaSupervisao(){
    return this->areaSupervisao;
}
void Gerente::aumentoSalarial(){
    this->salario = this->salario + (salario * (10/100));
    this->tributarSalario();
}
