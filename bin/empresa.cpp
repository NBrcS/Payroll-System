#include "empresa.h"

using namespace std;

Empresa::Empresa()
{
    for(int i = 0; i < 12; i++)
    {
        this->folhaSalarial[i] = 0.0;
    }
    funcionarios.clear();

    QString dir = qApp->applicationDirPath();
    QString banco = dir + "/bd_conection/db_empresa.db";

    QSqlDatabase bd = QSqlDatabase::addDatabase("QSQLITE");
    bd.setDatabaseName(banco);

    if(!bd.open()) qDebug() << "O banco de dados não está aberto";
    else{
        QSqlQuery query;
        query.prepare("select * from tb_funcionario");

        if(query.exec()){
            while(query.next()){
                Funcionario* funcionario = nullptr;

                QString cod = query.value(1).toString();
                QString nome = query.value(2).toString();
                QString telefone = query.value(3).toString();
                QString endereco = query.value(4).toString();
                QString salario = query.value(6).toString();
                int dia = query.value(9).toInt();
                int mes = query.value(10).toInt();
                int ano = query.value(11).toInt();

                tm data;
                data.tm_mday = dia;
                data.tm_mon = mes;
                data.tm_year = ano;

                QString designacao = query.value(5).toString();
                if(designacao.compare("Operador") == 0){
                    funcionario = new Operador( nome.toStdString(),
                                                endereco.toStdString(),
                                                telefone.toStdString(),
                                                designacao.toStdString(),
                                                data,  salario.toDouble());

                }else if(designacao.compare("Gerente") == 0){
                    QString areaSupervisao = query.value(12).toString();

                    funcionario = new Gerente( areaSupervisao.toStdString(),
                                               nome.toStdString(),
                                               endereco.toStdString(),
                                               telefone.toStdString(),
                                               designacao.toStdString(),
                                               data,  salario.toDouble());

                }else if(designacao.compare("Diretor") == 0){
                    QString areaSupervisao = query.value(12).toString();
                    QString graduacao =  query.value(13).toString();

                    funcionario = new Diretor( areaSupervisao.toStdString(),
                                               graduacao.toStdString(),
                                               nome.toStdString(),
                                               endereco.toStdString(),
                                               telefone.toStdString(),
                                               designacao.toStdString(),
                                               data, salario.toDouble());

                }else if(designacao.compare("Presidente") == 0){
                    QString formacaoAcademica = query.value(14).toString();
                    QString graduacao = query.value(13).toString();

                    funcionario = new Presidente( graduacao.toStdString(),
                                                  formacaoAcademica.toStdString(),
                                                  nome.toStdString(),
                                                  endereco.toStdString(),
                                                  telefone.toStdString(),
                                                  designacao.toStdString(),
                                                  data,  salario.toDouble());
                }

                QString salario_tributado = query.value(7).toString();
                QString valor_hora = query.value(8).toString();
                funcionario->setSalario_tributado(salario_tributado.toDouble());
                funcionario->setValor_hora(valor_hora.toDouble());
                funcionario->setCodFuncionario(cod.toStdString());

                funcionarios.push_back(funcionario);
            }
        }
        else qDebug() << "ERRO para coletar os dados dos funcionarios";

        query.prepare("select * from tb_dias_trabalhados");
        if(query.exec()){
            int j = 0;
            while(query.next()){
                for(int i = 0; i < 12; i++){
                    funcionarios[j]->setDiasTrabalhados(query.value(i).toInt(), i);

                }
                j++;
            }
        }
        else qDebug() << "Erro ao buscar na tabela de dias trabalhados";

        query.prepare("select * from tb_horas_trabalhadas");
        if(query.exec()){
            int j = 0;
            while(query.next()){
                for(int i = 0; i < 12; i++){
                    funcionarios[j]->setHoras_trabalhadas(query.value(i).toInt(), i);

                }
                j++;
            }
        }
        else qDebug() << "Erro ao buscar na tabela de horas trabalhadas";

        query.prepare("select * from tb_salario_mensal");
        if(query.exec()){
            int j = 0;
            while(query.next()){
                for(int i = 0; i < 12; i++){
                    funcionarios[j]->setSalario_mensal(query.value(i).toDouble(), i);

                }
                j++;
            }
        }
        else qDebug() << "Erro ao buscar na tabela de salarios mensais";

        query.prepare("select * from tb_folha_empresa");
        if(query.exec()){
            int i = 0;
            while(query.next()){
                folhaSalarial[i] = query.value(0).toDouble();

                i++;
            }
        }
        else qDebug() << "Erro ao coletar a folha salarial da empresa";
    }
}

Empresa::~Empresa()
{
    QSqlQuery query;


    if((query.exec("DELETE FROM tb_funcionario") &&
        query.exec("DELETE FROM tb_folha_empresa") &&
        query.exec("DELETE FROM tb_dias_trabalhados") &&
        query.exec("DELETE FROM tb_salario_mensal") &&
        query.exec("DELETE FROM tb_horas_trabalhadas"))){

        QSqlQuery query2;

        for(int i = 0; i < funcionarios.size(); i++){
            QString name = QString::fromStdString(funcionarios[i]->getNome());
            QString cod = QString::fromStdString(funcionarios[i]->getCodFuncionario());
            QString telefone = QString::fromStdString(funcionarios[i]->getTelefone());
            QString endereco = QString::fromStdString(funcionarios[i]->getEndereco());
            QString salario = QString::number(funcionarios[i]->getSalario());
            tm data = funcionarios[i]->getDataIngresso();

            QString dia = QString::number(data.tm_mday);
            QString mes = QString::number(data.tm_mon);
            QString ano = QString::number(data.tm_year);

            QString salario_tributado = QString::number(funcionarios[i]->getSalario_tributado());
            QString valor_hora = QString::number(funcionarios[i]->getValor_hora());

            QString designacao = QString::fromStdString(funcionarios[i]->getDesignacao());

            if(designacao.compare("Operador") == 0){
                query2.prepare("insert into tb_funcionario (cod_funcionario,nome_funcionario,telefone_funcionario,endereco_funcionario,"
                                                            "designacao_funcionario,salario_funcionario,salario_tributado,valor_hora,"
                                                            "dia_funcionario,mes_funcionario,ano_funcionario)"
                                "values "
                                                            "('"+cod+"','"+name+"','"+telefone+"','"+endereco+"','"+designacao+"',"
                                                            "'"+salario+"','"+salario_tributado+"','"+valor_hora+"',"
                                                            "'"+dia+"','"+mes+"','"+ano+"')");

            }else if(designacao.compare("Gerente") == 0){
                QString areaSupervisao = QString::fromStdString(( (Gerente* ) funcionarios[i])->getAreaSupervisao());
                query2.prepare("insert into tb_funcionario (cod_funcionario,nome_funcionario,telefone_funcionario,endereco_funcionario,"
                                                            "designacao_funcionario,salario_funcionario,salario_tributado,valor_hora,"
                                                            "dia_funcionario,mes_funcionario,ano_funcionario,areaSupervisao)"
                               "values "
                                                            "('"+cod+"','"+name+"','"+telefone+"','"+endereco+"','"+designacao+"',"
                                                                "'"+salario+"','"+salario_tributado+"','"+valor_hora+"',"
                                                                "'"+dia+"','"+mes+"','"+ano+"','"+areaSupervisao+"')");


            }else if(designacao.compare("Diretor") == 0){
                QString areaSupervisao = QString::fromStdString(( (Diretor* ) funcionarios[i])->getAreaSupervisao());
                QString graduacao =  QString::fromStdString(( (Diretor* ) funcionarios[i])->getAreaFormacao());
                query2.prepare("insert into tb_funcionario (cod_funcionario,nome_funcionario,telefone_funcionario,endereco_funcionario,"
                                                            "designacao_funcionario,salario_funcionario,salario_tributado,valor_hora,"
                                                            "dia_funcionario,mes_funcionario,ano_funcionario,areaSupervisao,graduacao)"
                               "values "
                                                            "('"+cod+"','"+name+"','"+telefone+"','"+endereco+"','"+designacao+"',"
                                                            "'"+salario+"','"+salario_tributado+"','"+valor_hora+"',"
                                                            "'"+dia+"','"+mes+"','"+ano+"','"+areaSupervisao+"','"+graduacao+"')");


            }else if(designacao.compare("Presidente") == 0){
                QString formacaoAcademica = QString::fromStdString(( (Presidente* ) funcionarios[i])->getFormacaoMaxima());
                QString graduacao = QString::fromStdString(( (Presidente* ) funcionarios[i])->getAreaFormacao());
                query2.prepare("insert into tb_funcionario (cod_funcionario,nome_funcionario,telefone_funcionario,endereco_funcionario,"
                                                            "designacao_funcionario,salario_funcionario,salario_tributado,valor_hora,"
                                                            "dia_funcionario,mes_funcionario,ano_funcionario,formacao_academica,graduacao)"
                               "values "
                                                            "('"+cod+"','"+name+"','"+telefone+"','"+endereco+"','"+designacao+"',"
                                                            "'"+salario+"','"+salario_tributado+"','"+valor_hora+"',"
                                                            "'"+dia+"','"+mes+"','"+ano+"','"+formacaoAcademica+"','"+graduacao+"')");
            }

            if(!query2.exec()) qDebug() << "Erro ao inserir funcionario no banco de dados";
            else{
                QSqlQuery query3;
                query3.exec("insert into tb_dias_trabalhados (Janeiro,Fevereiro,Marco,Abril,"
                                                                "Maio,Junho,Julho,Agosto,"
                                                                "Setembro,Outubro,Novembro,Dezembro) "
                            "values "
                            "('"+QString::number(funcionarios[i]->getDiasTrabalhados(0))+"','"+QString::number(funcionarios[i]->getDiasTrabalhados(1))+"',"
                            "'"+QString::number(funcionarios[i]->getDiasTrabalhados(2))+"','"+QString::number(funcionarios[i]->getDiasTrabalhados(3))+"',"
                            "'"+QString::number(funcionarios[i]->getDiasTrabalhados(4))+"','"+QString::number(funcionarios[i]->getDiasTrabalhados(5))+"',"
                            "'"+QString::number(funcionarios[i]->getDiasTrabalhados(6))+"','"+QString::number(funcionarios[i]->getDiasTrabalhados(7))+"',"
                            "'"+QString::number(funcionarios[i]->getDiasTrabalhados(8))+"','"+QString::number(funcionarios[i]->getDiasTrabalhados(9))+"',"
                            "'"+QString::number(funcionarios[i]->getDiasTrabalhados(10))+"','"+QString::number(funcionarios[i]->getDiasTrabalhados(11))+"')");

                query3.exec("insert into tb_horas_trabalhadas (Janeiro,Fevereiro,Marco,Abril,"
                                                                "Maio,Junho,Julho,Agosto,"
                                                                "Setembro,Outubro,Novembro,Dezembro) "
                            "values "
                            "('"+QString::number(funcionarios[i]->getHorasExtras(0))+"','"+QString::number(funcionarios[i]->getHorasExtras(1))+"',"
                            "'"+QString::number(funcionarios[i]->getHorasExtras(2))+"','"+QString::number(funcionarios[i]->getHorasExtras(3))+"',"
                            "'"+QString::number(funcionarios[i]->getHorasExtras(4))+"','"+QString::number(funcionarios[i]->getHorasExtras(5))+"',"
                            "'"+QString::number(funcionarios[i]->getHorasExtras(6))+"','"+QString::number(funcionarios[i]->getHorasExtras(7))+"',"
                            "'"+QString::number(funcionarios[i]->getHorasExtras(8))+"','"+QString::number(funcionarios[i]->getHorasExtras(9))+"',"
                            "'"+QString::number(funcionarios[i]->getHorasExtras(10))+"','"+QString::number(funcionarios[i]->getHorasExtras(11))+"')");

                query3.exec("insert into tb_salario_mensal (Janeiro,Fevereiro,Marco,Abril,"
                                                                "Maio,Junho,Julho,Agosto,"
                                                                "Setembro,Outubro,Novembro,Dezembro) "
                            "values "
                            "('"+QString::number(funcionarios[i]->get_SalarioMes(0))+"','"+QString::number(funcionarios[i]->get_SalarioMes(1))+"',"
                            "'"+QString::number(funcionarios[i]->get_SalarioMes(2))+"','"+QString::number(funcionarios[i]->get_SalarioMes(3))+"',"
                            "'"+QString::number(funcionarios[i]->get_SalarioMes(4))+"','"+QString::number(funcionarios[i]->get_SalarioMes(5))+"',"
                            "'"+QString::number(funcionarios[i]->get_SalarioMes(6))+"','"+QString::number(funcionarios[i]->get_SalarioMes(7))+"',"
                            "'"+QString::number(funcionarios[i]->get_SalarioMes(8))+"','"+QString::number(funcionarios[i]->get_SalarioMes(9))+"',"
                            "'"+QString::number(funcionarios[i]->get_SalarioMes(10))+"','"+QString::number(funcionarios[i]->get_SalarioMes(11))+"')");
            }
        }

        for(int i = 0; i < 12; i++)
            query2.exec("insert into tb_folha_empresa (folha_mensal) values ('"+QString::number(folhaSalarial[i])+"')");
    }
    else qDebug() << "Banco não conseguiu ser limpo";
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
                if(funcionarios[i]->getNome().find(parametros[0]))
                {
                    igual = false;
                }
                else igual = true;

            }

            //endereco
            if(existe[1]){
                if(funcionarios[i]->getEndereco().find(parametros[1]))
                {
                    igual = false;
                }
                else igual = true;

            }

            //codigo
            if(existe[2]){
                if(funcionarios[i]->getCodFuncionario().find(parametros[2]))
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

