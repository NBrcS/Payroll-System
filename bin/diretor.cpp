#include "diretor.h"

Diretor::Diretor() : Funcionario(3){

}
Diretor::Diretor(string areaSupervisao, string areaFormacao, string nome, string endereco, string telefone, string designacao, tm dataIngresso, double salario)
    : Funcionario(nome, endereco, telefone, designacao, dataIngresso, salario){
    this->areaSupervisao = areaSupervisao;
    this->areaFormacao = areaFormacao;
}
void Diretor::setAreaSupervisao(string areaSupervisao){
    this->areaSupervisao = areaSupervisao;
}
void Diretor::setAreaFormacao(string areaFormacao){
    this->areaFormacao = areaFormacao;
}
string Diretor::getAreaSupervisao(){
    return this->areaSupervisao;
}
string Diretor::getAreaFormacao(){
    return this->areaFormacao;
}
void Diretor::aumentoSalarial(){
    this->salario = this->salario + (salario * (20/100));
    this->tributarSalario();
}
