#include "Empresa.h"
#include "Funcionario.h"
#include <iomanip>
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

/*
*  avancarDia avanca um dia em relacao a data de inicio dada como parametro
*  e retorna essa data em forma de struct tm disponibilizada na biblioteca
*  <ctime>
*
*  NAO ESTAO INCLUSOS ANOS BISSEXTOS
*/
tm avancarDia(tm data_inicio)
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
*   adicionarFuncionario adiciona um ubjeto dinamico da classe Funcionario 
*   na ultima posicao vetor de funcionarios da classe Empresa
*
*/
void Empresa::adicionarFuncionario(Funcionario* fun_)
{
    funcionarios.push_back(fun_);
}

/*
*
*   O metodo editarFuncionario requisita ao usuario qual funcionario ele 
*   deseja editar e depois qual atributo deseja alterar. O atributo sera 
*   editado a parte do metodo editar da classe do funcionario escolhido
*
*/
void Empresa::editarFuncionario()
{
    int escolha, indice = 0;
    bool existe = false;

    do
    {
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
                existe = true;
                break;
            }
            indice++;
        }

        if(existe == false) 
        {
            cout << "Este funcionario nao existe, tente novamente por favor" << endl
                 << endl;
            indice = 0;
        }

    } while (existe == false);

    existe = false;
    do
    {
        cout << "Escolha agora qual aributo deseja alterar:" << endl
            << endl;
        funcionarios[indice].exibirAtributos();

        cout << "Escolha: ";
        cin >> escolha;
        cin.ignore();

        try
        {
            funcionarios[indice].editar(escolha);

            existe = true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';

            cout << "Atributo nao encontrado, por favor tente novamente" << endl;
            existe = false;
        }

    } while (existe == false);

}

/*
*
*   O metodo excluirFuncionario requisita ao usuario qual funcionario
*   ele deseja excluir, o apaga e reorganiza o vector funcionarios
*
*/
void Empresa::excluirFuncionario()
{
    int escolha, indice = 0;
    bool existe = false;

    do
    {

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
                existe = true;
                break;
            }
            indice++;
        }
        
        if(existe == false)
        {
            cout << "Funcionario nao encontrado, por favor tente novamente" << endl
                 << endl;
            indice = 0;
        } 

    }while(existe == false);

    funcionarios.erase(funcionarios[indice]);
}

/*
*
*   O metodo exibirFuncionario requisita ao usuario qual funcionario
*   ele quer ver e exibe todos os seus atributos a partir do metodo
*   exibirAtributos presente na classe do objeto funcionario
*
*/
void Empresa::exibirFuncionario()
{
    int escolha, indice = 0;
    bool existe = false;

    do
    {
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
                existe = true;
                break;
            }
            indice++;
        }

        if(existe == false)
        {
            cout << "Funcionario nao encontrado, por favor tente novamente" << endl
                 << endl;
            indice = 0; 
        }

    } while (existe == false);
    
    funcionarios[indice].exibirAtributos();   
}

/*
*   
*   O metodo exibirListaFuncionarios exibe a lista de todos os
*   funcionarios incluidos no vector funcionarios
*
*/
void Empresa::exibirListaFuncionarios()
{
    for(Funcionario* fun : funcionarios)
    {
        cout << fun->getNumero() << " - "
             << fun->getNome() << endl;
    }
    cout << endl;
}

/*
*
*   O metodo exibirListaFuncionarios_tipo requisita ao usuario qual tipo
*   de funcionario ele quer exibir e exibe todos os objetos desta classe 
*   especificada
*
*/
void Empresa::exibirListaFuncionarios_tipo()
{
    string tipo_s;
    int tipo_i;

    cout << "Digite o tipo de funcionario de deseja a lista exibida: " <<endl   
         <<endl;

    do
    {
        cout << "Escolha: ";
        cin >> tipo;

        if(tipo_i == 1) tipo_s = "Operador";
        else if(tipo_i == 2) tipo_s = "Gerente";
        else if(tipo_i == 3) tipo_s = "Diretor";
        else if(tipo_i == 4) tipo_s = "Presidente";
        else cout << "Tipo nao encontrado, por favor tente novamente" << endl;  

    } while (tipo_i > 4 || tipo_i < 1);
    
    for(Funcionario* fun : funcionarios)
    {
        if(fun->getTipo() == tipo_s)
        {
            cout << fun->getNumero() << " - "
                 << fun->getNome() << endl;
        }
    }
    cout << endl;
}

/*
*
*   O metodo aumentoSalarioGeral realiza um aumento no salario de todos os funcionarios
*   no vector funcionarios, variando a depender de cada implementacao de aumento de salario
*   na classe de cada objeto
*   
*/
void Empresa::aumentoSalarioGeral()
{
    for(int i = 0; i < funcionarios.size(); i++)
    {
        funcionarios[i].aumentarSalario();
    }
}

/*
*
*   O metodo calcularFolhaSalarial requisita ao usuario qual mes 
*   ele deseja calcular e exibira o resultado da soma dos salarios 
*   de todos os funcionarios nesse mes
*
*/
void Empresa::calcularFolhaSalarial()
{   
    cout << setprecision(2) << fixed;
    int escolha;

    do
    {
        cout << "Escolha o mes para calcular a folha salarial" << endl
             << endl;

        cout << "Escolha: ";
        cin >> escolha;

        if(escolha < 1 || escolha > 12) cout << "Mes invalido, tente novamente por favor." << endl;

    } while (escolha < 1 || escolha > 12);
    

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

/*
*
*   O metodo imprimirFolhaSalarial_Funcionario requisita ao usuario qual funcionario
*    e qual o mes ele quer calcular a folha salarial, e exibe o seu resultado
*
*/
void Empresa::imprimirFolhaSalarial_Funcionario()
{
    cout << setprecision(2) << fixed;

    int escolha, indice = 0;
    double folha = 0;
    bool existe = false;

    do
    {
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
                existe = true;
                break;
            }
            indice++;
        }

        if(existe == false)
        {
            cout << "Funcionario nao encontrado, por favor tente novamente" << endl
                 << endl;
            indice = 0;             
        }

    }while(existe == false);


    for(int i = 0; i < 12; i++)
    {
        folha += funcionarios[indice].folhaSalarial[i];
    }

    cout << "O total foi de: R$ " << folha << endl;

}

/*
*
*   o metodo imprimirFolhaSalarial_Empresa solicita ao usuario qual folha salarial
*   ele deseja calcular e a exibe
*
*/
void Empresa::imprimirFolhaSalarial_Empresa()
{
    cout << setprecision(2) << fixed;

    int escolha;
    double folha = 0;

    do
    {

        cout << "Qual folha salarial deseja buscar?" << endl << endl
            << "[ 1 ] - Anual " << endl
            << "[ 2 ] - mensal " << endl
            << endl;
         
        cout << "Escolha: ";
        cin >> escolha;
        cin.ignore();  

        if(escolha > 2 || escolha < 1) cout << "Opcao invalida, por favor, tente novamente." << endl;

    } while (escolha > 2 || escolha < 1);
    
    switch (escolha)
    {
        case 1:
            for(int i = 0; i < 12; i++)
            {
                folha += folhaSalarial[i];
            }
        
            break;
        case 2:
            do
            {
                cout << "Digite o mês o qual deseja buscar: ";
                cout << endl;

                cout << "escolha";
                cin >> escolha;
                cin.ignore();

                if(escolha < 1 || escolha > 12)
                {
                    cout << "Opcao invalida, por favor, tente novamente" << endl;
                }

            }while(escolha < 1 || escolha > 12);

                folha = folhaSalarial[escolha];
            
            break;
        default:
            break;
    }

    cout << "Total calculado: R$ " << folha << endl;
}

/*
*
*   O metodo  buscarFuncionario solicita ao usuario o modo de busca no qual ele 
*   deseja buscar um funcionario e exibe todos os funcionarios encontrados a partir
*   do motor de busca escolhido e dos parametros fornecidos
*
*/
void Empresa::buscarFuncionario()
{
    int escolha;
    vector<int> encontrados;
    bool existe = false;

    do{
        cout << "Selecione a forma no qual deseja buscar o funcionario: " << endl
            << endl;

        cout << "[ 1 ] - Nome" << endl
             << "[ 2 ] - Data de ingresso" << endl
             << "[ 3 ] - Endereço" << endl;

        cout << "Escolha: ";
        cin >> escolha;
        cin.ignore();

        if(escolha < 1 || escolha > 3) cout << "Opcao invalida, por favor, tente novamente" << endl;
    }while(existe == false);


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
                tm_inicial = avancarDia(tm_inicial);

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
