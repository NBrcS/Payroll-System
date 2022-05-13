Olá!! esse projeto será feito com os participantes Lucas e saulo, os quais estarão listados como "forks" no repositório.

Este será um projeto CRUD em C++ de um sistema de folha de pagamento, o qual terá uma interface gráfica e um armazenamento de informações em arquivos .txt.

Segue, o desafio proposto para este sistema, e em breve será atualizada uma to do list pelo bem da organização do projeto

<blockquote>
    <p>
       
        Desenvolva um Sistema de Gerenciamento de Folha de Pagamento para uma determinada
        empresa. Nesta empresa há quatro tipos de funcionários: operador, gerente, diretor e
        presidente.
        O sistema deve possuir os tipos Operador, Gerente, Diretor e Presidente. Todos devem possuir
        os atributos: número do código do funcionário, nome, endereço, telefone, data de ingresso,
        designação (indica se é operador, gerente, diretor ou presidente) e salário. Tipos específicos de
        
        funcionários, possuem informações adicionais que precisam ser recuperadas:
        ● Gerente: nome da área de supervisão
        ● Diretor: nome da área de supervisão e área de formação
        ● Presidente: área de formação e qual formação acadêmica máxima (por exemplo,
        especialista, mestre, doutor...)
        
        Além disso, este projeto deve ter outras classes e subclasses, crie classes para gerenciar os
        requisitos. Não façam tudo na função main() .
        Requisitos Gerais:
        

        a) Adicionar um novo funcionário: Todos os atributos dos funcionários devem ser lidos e
        armazenados no objeto correspondente.
        
        b) Modificar ou editar um registro de funcionário: Os usuários podem editar o número de
        código do funcionário, data de ingresso (dia, mês e ano), nome, endereço, telefone, designação
        e salário.
        
        c) Excluir um registro de funcionário: O registro de um funcionário pode ser excluído usando o
        código do funcionário. Uma mensagem de confirmação de exclusão mostra se o usuário
        realmente deseja excluir o registro do arquivo. Caso o funcionário seja um presidente ou
        diretor, ele não poderá ser removido.
        
        d) Exibir registro de funcionário: Ao inserir o número de código do funcionário, os usuários
        podem acessar todas as informações fornecidas relacionadas a um determinado funcionário
        por meio desta função.
        
        e) Exibir lista de Funcionários: Este recurso exibe o registro de todos os funcionários
        
        f) Exibir lista de Funcionários por tipo: Este recurso exibe o registro de todos os funcionários de
        um determinado tipo.
        
        g) Conceder aumento para os funcionários: este recurso ao ser solicitado deverá rodar uma
        rotina de aumento de salário para todos os funcionários. Sendo os percentuais de aumento:
        ● Operador: 5%
        ● Gerente: 10%
        ● Diretor: 20%
        ● Presidente 30%
        
        e) Calcular Folha Salarial: Responsável por realizar o cálculo de salário de todos os funcionários
        para um determinado mês. Assim, será solicitado do usuário o mês a que se refere a folha
        salarial. Caso a folha para este mês já tenha sido calculada, exibir mensagem alertando que a
        folha para o seguinte mês já foi calculada. Deverá ser executada uma rotina que irá gerar
        aleatoriamente, mas apenas uma única vez, as informações como o número de dias
        trabalhados no mês pelo funcionário e o número de horas extras trabalhadas. Usar regra que a
        hora-extra equivale ao dobro daquilo pago para hora normal. Deverá também ser contabilizado
        os descontos relativos ao imposto de renda e previdência social.
       
        f) Imprimir uma Folha de Salário do Funcionário: Esse recurso também solicita o código do
        funcionário ou nome completo. Deve constar o salário base, descontos e salário líquido do
        empregado.
       
        g) Imprimir a folha salarial empresa: Esse recurso dá opção de o usuário escolher ou a folha
        anual calculando o somatório de salário de cada empregado ou uma folha mensal, sendo que
        para esta última será solicitado qual mês do ano.
        
        h) Buscar: recurso que permite a busca de funcionários pelo:
        ● Nome: fazer busca parcial
        ● Data de ingresso (dia, mês e ano): fazer por intervalo de tempo
        ● Endereço: fazer busca parcial
       
        As informações de registro de funcionário exibidas são aquelas fornecidas ao adicionar um
        novo registro de funcionário.
       
        É esperado várias classes, herança, polimorfismo e classes abstratas, todas estas relações
        devem ser descritas no documento.
        

        Requisitos Extras:
        
        a) Todos os dados devem ser salvos em arquivo. Criar funções para salvamento e recuperação
        dos dados em arquivo ou em Banco de Dados.
       
        b) Interface gráfica com o usuário (GUI). Podem usar bibliotecas gráficas como Qt ou GTK, ou
        outra.
        
        c) Obter o endereço do funcionário baseado no CEP, para isso baixe o json com os dados do
        CEP utilizando algum serviço gratuito como o do https://viacep.com.br.
       
        d) Fotografar o usuário no momento do cadastro, para isso pode ser utilizada alguma biblioteca
        externa como a OpenCV, ou outra biblioteca, ou algum programa externo.
       
        e) Execução dos comandos através de comando de voz.

        
        Entrega:
        ● Código fonte + apresentação do projeto;
        ● Satisfazer todos os requisitos gerais listados acima.
        ● Satisfazer pelo menos dois Requisitos Extras.
        ● Comentários de documentação adequados no código.
        Os projetos devem ser desenvolvidos em grupos de até 3 alunos
        
        </p>
    </blockquote>