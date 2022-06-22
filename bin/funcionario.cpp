#include "funcionario.h"
#include <ctime>
#include <cstdlib>
#include <QDebug>

Funcionario::Funcionario(int t){
    switch(t){
        case 0:
            this->designacao = "undefined";

            break;
        case 1:
            this->designacao = "Operador";

            break;
        case 2:
            this->designacao = "Gerente";

            break;
        case 3:
            this->designacao = "Diretor";

            break;
        case 4:
            this->designacao = "Presidente";

            break;
        default:
            break;
    }
}
Funcionario::Funcionario(string nome, string endereco, string telefone, string designacao, tm dataIngresso, double salario){
    this->nome = nome;
    this->endereco = endereco;
    this->telefone = telefone;
    this->designacao = designacao;
    this->dataIngresso.tm_mday = dataIngresso.tm_mday;
    this->dataIngresso.tm_mon = dataIngresso.tm_mon;
    this->dataIngresso.tm_year = dataIngresso.tm_year;
    this->salario = salario;
    tributarSalario();

    double salario_mensal;
    valor_hora = (salario_tributado / 25) / 24;
    for(int i = 0; i < 12; i++){
        horasTrabalhadas[i] = rand() % 20;
        diasTrabalhados[i] = rand() % 25;

        salario_mensal = diasTrabalhados[i] * (valor_hora * 8)
                         + horasTrabalhadas[i] * (valor_hora * 1.5);

        salariosMensais[i] = salario_mensal;
    }

    int cod = (rand() % 1000 + 1000);
    this->codFuncionario = to_string(cod);
}

void Funcionario::setCodFuncionario(string CodFuncionario){
    this->codFuncionario = CodFuncionario;
}
void Funcionario::setNome(string nome){
    this->nome = nome;
}
void Funcionario::setEndereco(string endereco){
    this->endereco = endereco;
}
void Funcionario::setTelefone(string telefone){
    this->telefone = telefone;
}
void Funcionario::setDesignacao(string designacao){
    this->designacao = designacao;
}
void Funcionario::setDataIngresso(tm dataIngresso){
    this->dataIngresso.tm_mday = dataIngresso.tm_mday;
    this->dataIngresso.tm_mon = dataIngresso.tm_mon;
    this->dataIngresso.tm_year = dataIngresso.tm_year;
}
void Funcionario::setSalario(double salario){
    this->salario = salario;

    tributarSalario();
}
double Funcionario::get_SalarioMes(int index){
    return salariosMensais[index];
}

string Funcionario::getCodFuncionario(){
    return this->codFuncionario;
}
string Funcionario::getNome(){
    return this->nome;
}
string Funcionario::getEndereco(){
    return this->endereco;
}
string Funcionario::getTelefone(){
    return this->telefone;
}
string Funcionario::getDesignacao(){
    return this->designacao;
}
tm Funcionario::getDataIngresso(){
    return this->dataIngresso;
}
double Funcionario::getSalario(){
    return this->salario;
}
bool Funcionario::ComparaDatas(tm data){
    if(this->dataIngresso.tm_mday == data.tm_mday &&
        this->dataIngresso.tm_mon == data.tm_mon &&
        this->dataIngresso.tm_year == data.tm_year){
        return true;
    }else{
        return false;
    }
}

void Funcionario::tributarSalario()
{
    double parte_previdencia = 0.0;
    double parte_IR;


    if(salario < 1212){
        parte_previdencia = salario * (7.5/100);

    }else if(salario >= 1212.01 && salario <= 2427.35){
        parte_previdencia = salario * (9.0/100);

    }else if(salario >= 2427.36 && salario <= 3641.03){
        parte_previdencia = salario * (12.0/1000);

    }else{
        parte_previdencia = salario * (14.0/100);
    }

    if(salario < 1903.98){
        parte_IR = 0;
    }
    else if(salario > 1903.99 && salario < 2826.65){
        parte_IR = salario * (7.5/100);
    }
    else if(salario > 2826.66 && salario < 3751.05){
        parte_IR = salario * (15/100);
    }
    else if(salario > 3751.06 && salario < 4664.68){
        parte_IR = salario * (22.5/100);
    }
    else{
        parte_IR = salario * (27.5/100);
    }

    salario_tributado = salario - parte_previdencia - parte_IR;
}

int Funcionario::getDiasTrabalhados(int index)
{
    return diasTrabalhados[index];
}
int Funcionario::getHorasExtras(int index)
{
    return horasTrabalhadas[index];
}

double Funcionario::getValor_hora() const
{
    return valor_hora;
}

void Funcionario::setValor_hora(double newValor_hora)
{
    valor_hora = newValor_hora;
}

double Funcionario::getSalario_tributado() const
{
    return salario_tributado;
}

void Funcionario::setSalario_tributado(double newSalario_tributado)
{
    salario_tributado = newSalario_tributado;
}

void Funcionario::setDiasTrabalhados(int dias, int index)
{
    diasTrabalhados[index] = dias;
}

void Funcionario::setHoras_trabalhadas(int horas, int index)
{
    horasTrabalhadas[index] = horas;
}

void Funcionario::setSalario_mensal(double salario, int index)
{
    salariosMensais[index] = salario;
}



