#include "empresa.h"

#include "operador.h"
#include "gerente.h"
#include "diretor.h"
#include "presidente.h"

#include <iomanip>
#include <vector>
#include <ctime>
#include <string>
#include <iostream>
#include <QDebug>

using namespace std;

Empresa::Empresa()
{
    for(int i = 0; i < 12; i++)
    {
        this->folhaSalarial[i] = 0.0;
    }
}


/*
*  avancarDia avanca um dia em relacao a data de inicio dada como parametro
*  e retorna essa data em forma de struct tm disponibilizada na biblioteca
*  <ctime>
*
*  NAO ESTAO INCLUSOS ANOS BISSEXTOS
*/
tm avancarDia(tm& data_inicio)
{
    data_inicio.tm_mday++;

    if ((data_inicio.tm_mon == 2 && data_inicio.tm_mday > 28) ||
            ((data_inicio.tm_mon == 4 || data_inicio.tm_mon == 6 || data_inicio.tm_mon == 9 || data_inicio.tm_mon == 11) && data_inicio.tm_mday > 30) ||
            ((data_inicio.tm_mon == 1 || data_inicio.tm_mon == 3 || data_inicio.tm_mon == 5 || data_inicio.tm_mon == 7 || data_inicio.tm_mon == 8 || data_inicio.tm_mon == 10 || data_inicio.tm_mon == 12) && data_inicio.tm_mday > 31))
    {

        data_inicio.tm_mday = 1;
        data_inicio.tm_mon++;

        if (data_inicio.tm_mon > 12)
        {
            data_inicio.tm_mon = 1;
            data_inicio.tm_year++;
        }
    }

    return data_inicio;
}


/*
 *
 *  getVectorSize retorna o tamanho do vetor de funcionarios
 *
 */
int Empresa::getVectorSize()
{
    return funcionarios.size();
}

/*
 *
 * get_Func_com_index retorna o Funcionario do vetor de funcionarios
 * que tenha o indice passado como parametro
 *
 */
Funcionario* Empresa::get_Func_com_index(int index)
{
    return this->funcionarios[index];
}

/*
 *
 * empresa_anual retorna um vector do tipo double com os valores
 * mensais da folha salarial em cada mes ate o indice 11 e,
 * como ultimo parametro, o total anual somado
 *
 */
vector<double> Empresa::empresa_anual()
{
    vector<double> valores;
    double mensal, total = 0.0;

    for(int i = 0; i < 12; i++)
    {
        mensal = empresa_mensal(i);
        total += mensal;

        valores.push_back(mensal);
    }
    valores.push_back(total);

    return valores;
}

/*
 * empresa_mensal retorna um double com o valor da folha salarial do
 * mes passado como parametro de 0 a 11
 */
double Empresa::empresa_mensal(int index)
{

    bool notExists = (this->folhaSalarial[index] == 0.0);
    if(notExists){
        for(int i = 0; i < funcionarios.size(); i++)
        {
            this->folhaSalarial[index] += funcionarios[i]->get_SalarioMes(index);
        }
    }

    return this->folhaSalarial[index];
}

/*
 *
 * funcionario_anual retorna um vector do tipo double com os valores
 * mensais da folha salarial em cada mes ate o indice 11 e,
 * como ultimo parametro, o total anual somado
 *
 */
vector<double> Empresa::funcionario_anual(int index)
{
    vector<double> valores;
    double mensal, total = 0.0;

    for(int i = 0; i < 12; i++)
    {
        mensal = funcionario_mensal(index, i);
        total += mensal;

        valores.push_back(mensal);
    }
    valores.push_back(total);

    return valores;

}

/*
 * empresa_mensal retorna um double com o valor da folha salarial do
 * mes passado como parametro de 0 a 11
 */
double Empresa::funcionario_mensal(int index_func, int index_mes)
{
    return this->funcionarios[index_func]->get_SalarioMes(index_mes);
}

/*
 *
 * funcionarios_achados retorna um vector de valores inteiros que representara
 * o indice dos funcionarios achados de acordo com os parametros passados em um
 * vector string q foi tratado no botao de busca, formulario edit
 *
 */
vector<int> Empresa::funcionarios_achados(vector<string> parametros)
{
    vector<bool> existe;
    vector<int> achados;
    bool achou_um = false;

    for(const string &str : parametros)
    {
        if(str.compare("")) existe.push_back(true);
        else existe.push_back(false);
    }

    bool todos_vazios = true;
    for(bool b : existe)
    {
        if(b) todos_vazios = false;
        achou_um = true;
    }

    if(todos_vazios)
    {
        for(int i = 0; i < funcionarios.size(); i++)
        {
            achados.push_back(i);
        }
    }
    else
    {
        bool igual;
        for(int i = 0; i < funcionarios.size(); i++)
        {
            igual = false;

            //nome
            if(existe[0]){
                if(funcionarios[i]->getNome().compare(parametros[0]))
                {
                    igual = false;
                }
                else igual = true;

            }

            //endereco
            if(existe[1]){
                if(funcionarios[i]->getEndereco().compare(parametros[1]))
                {
                    igual = false;
                }
                else igual = true;

            }

            //codigo
            if(existe[2]){
                if(funcionarios[i]->getCodFuncionario().compare(parametros[2]))
                {
                    igual = false;
                }
                else igual = true;

            }

            //designacao
            if(existe[3]){
                if(funcionarios[i]->getDesignacao().compare(parametros[3]))
                {
                    igual = false;
                }
                else igual = true;

            }

            //data
            if((existe[4] && existe[5] && existe[6]) && (existe[7] && existe[8] && existe[9]))
            {
                if((stoi(parametros[4]) > 28 && stoi(parametros[5]) == 02 ) ||
                    (stoi(parametros[7]) > 28 && stoi(parametros[8]) == 02 ))
                {
                    throw ("Fevereiro não pode ter mais que 28 dias");
                }


                tm data_inicio, data_fim;

                data_inicio.tm_mday = stoi(parametros[4]);
                data_inicio.tm_mon = stoi(parametros[5]);
                data_inicio.tm_year = stoi(parametros[6]);

                data_fim.tm_mday = stoi(parametros[7]);
                data_fim.tm_mon = stoi(parametros[8]);
                data_fim.tm_year = stoi(parametros[9]);

                igual = false;
                while(!compare_datas(data_inicio, data_fim))
                {
                    if(funcionarios[i]->ComparaDatas(data_inicio))
                    {
                        igual = true;
                        break;
                    }
                    avancarDia(data_inicio);
                }
            }

            if(igual)
            {
                achados.push_back(i);
                achou_um = true;
            }
        }
    }

    if(!achou_um)
    {
        throw ("Não foi encontrado um funcionário com estes parametros");
    }
    else
    {
        return achados;
    }

    existe.clear();
    achados.clear();
}

/*
 *
 *  compare_datas retorna true caso as datas passadas como parametro forem iguais
 *  e false caso elas diferenciem, nao sao considerados horarios
 *
 */
bool Empresa::compare_datas(tm data_inicio, tm data_final)
{
    if(data_inicio.tm_mday == data_final.tm_mday &&
            data_inicio.tm_mon == data_final.tm_mon &&
            data_inicio.tm_year == data_final.tm_year){
        return true;
    }
    else{
        return false;
    }
}

/*
 *
 * add_func Adiciona um funcionario ao vector de funcionarios
 *
 */
void Empresa::add_func(Funcionario* fun_)
{
    this->funcionarios.push_back(fun_);
}

/*
 *
 *  att_func atualiza o ponteiro de funcionario de indice passado como parametro
 *  para o ponteiro de funcionario tambem passado tambem como parametro
 *
 */
void Empresa::att_func(Funcionario* fun, int index)
{
    funcionarios[index] = fun;
}

/*
 *
 * aumentoSalarioGeral Raliza o aumento salarial
 * em todos os funcionarios nas seguintes proporções
 *
 * Operador - 5%
 * Gerente - 10%
 * Diretor - 15%
 * Presidente - 20%
 *
 */
void Empresa::aumentoSalarioGeral()
{
    for(int i = 0; i < funcionarios.size(); i++)
    {
        funcionarios[i]->aumentoSalarial();
    }
}

/*
 *
 * apagar_funcionario deleta o funcionario no indice passado como parametro
 * e automaticamente reorganiza o vector de funcionarios
 *
 */
void Empresa::apagar_funcionario(int index){
    this->funcionarios.erase(funcionarios.begin() + index);
}

