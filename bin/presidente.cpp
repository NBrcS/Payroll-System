#include "presidente.h"

Presidente::Presidente() : Funcionario(4){

}
Presidente::Presidente(string areaFormacao, string formacaoMaxima, string codFuncionario, string nome, string endereco, string telefone, string designacao, tm dataIngresso, double salario)
    : Funcionario(codFuncionario, nome, endereco, telefone, designacao, dataIngresso, salario){
    this->areaFormacao = areaFormacao;
    this->formacaoMaxima = formacaoMaxima;
}

void Presidente::setAreaFormacao(string areaFormacao){
    this->areaFormacao = areaFormacao;
}
void Presidente::setFormacaoMaxima(string formacaoMaxima){
    this->formacaoMaxima = formacaoMaxima;
}
string Presidente::getAreaFormacao(){
    return this->areaFormacao;
}
string Presidente::getFormacaoMaxima(){
    return this->formacaoMaxima;
}
void Presidente::aumentoSalarial(){
    this->salario = this->salario + (salario * (30/100));
    this->tributarSalario();
}
