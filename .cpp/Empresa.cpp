#include "Empresa.h"
#include "Funcionario.h"
#include <iomanip>
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

tm avancarDia()
{
    tm generico;

    generico.tm_mday++;

    if ((generico.tm_mon == 2 && generico.tm_mday > 28) || 
       ((generico.tm_mon == 4 || generico.tm_mon == 6 || generico.tm_mon == 9 || generico.tm_mon == 11) && generico.tm_mday > 30) ||
       ((generico.tm_mon == 1 || generico.tm_mon == 3 || generico.tm_mon == 5 || generico.tm_mon == 7 || generico.tm_mon == 8 || generico.tm_mon == 10 || generico.tm_mon == 12) && generico.tm_mday > 31))
       {
        
            generico.tm_mday = 1;
            generico.tm_mon++;

            if (generico.tm_mon > 12)
            {
                generico.tm_mon = 1;
                generico.tm_year++;
            }
    }

    return tm;
}

void Empresa::adicionarFuncionario(Funcionario* fun_)
{
    funcionarios.push_back(fun_);
}

void Empresa::editarFuncionario()
{
    int escolha, indice = 0;

    cout << "Escolha um funcionario dentre os listados a seguir: " << endl 
         << endl;
    this->exibirListaFuncionarios();

    cout << "Escolha: ";
    cin >> escolha;
    cin.ignore();

    for(Funcionario* fun : funcionarios)
    {
        if(fun->getNumero() == escolha)
        {
            break;
        }
        indice++;
    }

    cout << "Escolha agora qual aributo deseja alterar:" << endl
         << endl;
    this->exibirFuncionario();

    cout << "Escolha: ";
    cin >> escolha;
    cin.ignore();

    funcionarios[indice].editar(escolha);
}

void Empresa::excluirFuncionario()
{
    int escolha, indice = 0;

    cout << "Escolha um funcionario dentre os listados a seguir: " << endl 
         << endl;

    this->exibirListaFuncionarios();

    cout << "Escolha: ";
    cin >> escolha;
    cin.ignore();

    for(Funcionario* fun : funcionarios)
    {
        if(fun->getNumero() == escolha)
        {
            break;
        }
        indice++;
    }

    funcionarios.erase(funcionarios[indice]);
}

void Empresa::exibirFuncionario()
{
    int escolha, indice = 0;

    cout << "Escolha um funcionario dentre os listados a seguir: " << endl 
         << endl;
    this->exibirListaFuncionarios();

    cout << "Escolha: ";
    cin >> escolha;
    cin.ignore()

    for(Funcionario* fun : funcionarios)
    {
        if(fun->getNumero() == escolha)
        {
            break;
        }
        indice++;
    }

    funcionarios[indice].exibirAtributos();   
}

void Empresa::exibirListaFuncionarios()
{
    for(Funcionario* fun : funcionarios)
    {
        cout << fun->getNumero() << " - "
             << fun->getNome() << endl;
    }
    cout << endl;
}

void Empresa::exibirListaFuncionarios_tipo()
{
    string tipo;

    cout << "Digite o tipo de funcionario de deseja a lista exibida: " <<endl   
         <<endl;

    cout << "Escolha: ";
    cin >> tipo;

    for(Funcionario* fun : funcionarios)
    {
        if(fun->getTipo() == tipo)
        {
            fun->exibirAtributos();
        }
    }
}

void Empresa::aumentoSalarioGeral()
{
    for(int i = 0; i < funcionarios.size(); i++)
    {
        funcionarios.at(i).aumentarSalario();
    }
}

void Empresa::calcularFolhaSalarial()
{   
    cout << setprecision(2) << fixed;
    int escolha;

    cout << "Escolha o mes para calcular a folha salarial" << endl
         << endl;

    cout << "Escolha: ";
    cin >> escolha;

    if(folhaSalarial[escolha] != 0) cout << "Este mes ja foi calculado." << endl; 
    else
    {
        for(funcionarios* fun : funcionarios)
        {
            folhaSalarial[escolha] += fun->getSalario();
        }
    }

    cout << "O total foi de R$ " << folhaSalarial[escolha]
         << endl;
}

void Empresa::imprimirFolhaSalarial_Funcionario()
{
    cout << setprecision(2) << fixed;

    int escolha, indice = 0;
    double folha = 0;

    cout << "Escolha um funcionario dentre os listados a seguir: " << endl 
         << endl;
    this->exibirListaFuncionarios();

    cout << "Escolha: ";
    cin >> escolha;
    cin.ignore()

    for(Funcionario* fun : funcionarios)
    {
        if(fun->getNumero() == escolha)
        {
            break;
        }
        indice++;
    }

    for(int i = 0; i < 12; i++)
    {
        folha += funcionarios[indice].folhaSalarial[i];
    }

    cout << "O total foi de: R$ " << folha << endl;

}

void Empresa::imprimirFolhaSalarial_Empresa()
{
    cout << setprecision(2) << fixed;

    int escolha;
    double folha = 0;

    cout << "Qual folha salarial deseja buscar?"
         << "[ 1 ] - Anual "
         << "[ 2 ] - mensal " 
         << endl << endl;
         
    cout << "Escolha: ";
    cin >> escolha;
    cin.ignore();

    switch (escolha)
    {
        case 1:
            for(int i = 0; i < 12; i++)
            {
                folha += folhaSalarial[i];
            }
        
            break;
        case 2:
            cout << "Digite o mês o qual deseja buscar: ";
            cout << endl;

            cout << "escolha";
            cin >> escolha;
            cin.ignore();

            folha = folhaSalarial[escolha];

            break;
        default:
            break;
    }

    cout << "Total calculado: R$ " << folha << endl;
}

void Empresa::buscarFuncionario()
{
    int escolha;
    vector<int> encontrados;
    bool existe = false;

    cout << "Selecione a forma no qual deseja buscar o funcionario: " << endl
         << endl;

    cout << "[ 1 ] - Nome" << endl
         << "[ 2 ] - Data de ingresso" << endl
         << "[ 3 ] - Endereço" << endl;

    cout << "Escolha: ";
    cin >> escolha;
    cin.ignore();

    switch (escolha)
    {
        case 1:
            string name;

            cout << "Digite o nome do funcionario que deseja buscar: ";
            getline(cin, name);

            for (int i = 0; i < funcionarios.size(); i++)
            {
                if(funcionarios.getName().find(name) != -1 )
                {
                    existe = true;
                    encontrados.push_back(i);
                }
            }

            break;
        case 2:
            int dia, mes, ano;
            tm tm_inicial, tm_final;

            cout << "Digite o dia da data de inicio do periodo a ser procurado: ";
            cin >> dia;
            
            cout << "Digite o mes da data de inicio do periodo a ser procurado: "; 
            cin >> mes;

            cout << "Digite o ano da data de inicio do periodo a ser procurado: ";
            cin >> ano;

            tm_inicial.tm_mday = dia;
            tm_inicial.tm_mon = mes;
            tm_inicial.tm_year = ano;

            cout << "Digite o dia da data de fim do periodo a ser procurado: ";
            cin >> dia;
            
            cout << "Digite o mes da data de fim do periodo a ser procurado: "; 
            cin >> mes;

            cout << "Digite o ano da data de fim do periodo a ser procurado: ";
            cin >> ano;

            tm_final.tm_mday = dia;
            tm_final.tm_mon = mes;
            tm_final.tm_year = ano;

            cin.ignore();

            while(tm_inicial != tm_final)
            {
                tm_inicial = avancarDia();

                int indice = 0;
                for (Funcionario* fun : funcionarios)
                {
                    if (fun->getTm_dataDeIngresso() == tm_inicial)
                    {
                        existe = true;
                        encontrados.push_back(indice);
                    }

                    indice++;
                }
            }

            break;
        case 3:
            string endereco;

            cout << "Digite o endereço a ser procurado: ";
            getline(cin, endereco);

            int indice = 0;
            for(Funcionario* fun : funcionarios)
            {
                if(fun->getEndereco().find(endereco) != -1)
                {
                    existe = true;
                    encontrados.push_back(indice);
                }
            }

            break;
        default:
            break;
    }

    if(existe == false)
    {
        cout << "Nao existem funcionarios com esses parametros" << endl;
    }
    else
    {
        cout << "Este(s) eh(sao) o(s) funcionario(s) encontrado(s)" << endl 
             << endl;

        while (encontrados.empty() != true)
        {
            cout << funcionarios[encontrados.begin()]->getNumero() << " - "
                 << funcionarios[encontrados.begin()]->getNome() << endl;

            encontrados.pop_front();
        }
    }

    cout << endl;
}
