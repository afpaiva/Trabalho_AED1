/*Projeto final - Controle de vagas de estacionamento | Fase 2
Professor: Claudio Correa e Luiz Gomes
Dupla: Andr� Fonseca de Paiva e Fernando Thales Pereira
�lltima atualiza��o: 16/06/2020 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#ifdef _WIN32
# define CLEAR_SCREEN system("cls || clear");
#else
# define CLEAR_SCREEN puts("\x1b[H\x1b[2J");
#endif

#define QUANT_RUAS 3 //f[QUANTIDADE DE RUAS]
#define QUANT_VAGAS 20

void erro(int codErro);
int estacionaCarro (int rua);

typedef struct {
  char nome_rua[50];
  int num_vagas;
  int status_vagas[QUANT_VAGAS]; // 0 = vaga vazia / 1 = vaga ocupada
  float valor;
  } ruas;

typedef struct {
    char placa[10];
    int tempo; // vamos usar para saber se a vaga est� ocupada ou n�o
    int ruaID;
} carros;

int main (){

    setlocale (LC_ALL, "Portuguese");

    int opcaoMenu, i, escolha, opcaoMenuRelatorio;
    int acessoMenuRuas = 1, acessoMenuVagas = 0, acessoMenuValor = 0, acessoUsuario = 0;
    //vari�veis "acesso..." controlam os acessos ao menu, s�o booleanas
    int ruasOK = 0, vagasOK = 0, valorOK = 0;
    //variaveis "OK" para saber o que j� foi entrado
    ruas estacionamento[QUANT_RUAS];
    int valida; // a2[Para valida��es em geral]
    float validaf; // a2[Para valida��es em geral]
    int rua_escolhida; // registra temporariamente a rua escolhida
    carros carro[QUANT_VAGAS*QUANT_RUAS]; // struct carros com total de vagas disponiveis
    int carroID; // guarda provisoriamente o carro que est� sendo tratado

    //zerando os tempos das vagas para facilitar no relat�rio depois
    for (int i = 0; i < QUANT_VAGAS*QUANT_RUAS; i++)
        carro[i].tempo = 0;

    //zerando os status das vagas
    for (int i = 0; i < QUANT_RUAS; i++)
        for (int j = 0; j < QUANT_VAGAS; j++)
            estacionamento[i].status_vagas[j] = 0;

    do{
        CLEAR_SCREEN
        printf ("\n+----------------------------------------------+\n|      Sistema de Estacionamento Rotativo      |\n+----------------------------------------------+\n");

        printf ("\n       ***** Menu *****               \n");
        printf ("\n     Selecione a op��o desejada     \n\n");

        if (acessoMenuRuas)
          printf ("Cadastrar Ruas..................[1]\n");
          else
          printf ("Cadastrar Ruas..................[-]\n");

        if (acessoMenuVagas)
          printf ("Cadastro de N�meros de Vagas....[2]\n");
          else
          printf ("Cadastro de N�meros de Vagas....[-]\n");

        if (acessoMenuValor)
          printf ("Cadastro de Valor de Vagas......[3]\n");
          else
          printf ("Cadastro de Valor de Vagas......[-]\n");

        if (acessoUsuario){
          printf ("Estacionar um Carro.............[4]\n");
          printf ("Liberar Vaga....................[5]\n");
          printf ("Emitir Relat�rio................[6]\n");
        }else{
          printf ("Estacionar um Carro.............[-]\n");
          printf ("Liberar Vaga....................[-]\n");
          printf ("Emitir Relat�rio................[-]\n");
        }

        printf ("Sair............................[0]\n\n");


        printf("Digite a op��o desejada: ");
        scanf("%i",&opcaoMenu);
        getchar(); //a[coloquei um getchar aqui]

        if (opcaoMenu<0 || opcaoMenu>6) erro(1); // a[erro � uma fun��o l� em baixo]

        switch(opcaoMenu){

            //**Cadastrar Ruas
            case 1:

                if (acessoMenuRuas){
                  for (int i = 0; i < QUANT_RUAS; i++)
                  {
                    printf("\n\tInsira o nome da %i� rua a ser cadastrada: ",i+1);
                    scanf("%[^\n]s",estacionamento[i].nome_rua);
                    getchar();
                    // a[Cadastro de ruas OK!]
                  }
                  printf("\n\nRuas cadastradas com sucesso.\nPressione enter para continuar...\n");
                  getchar();
                  ruasOK = 1;
                  acessoMenuRuas = 0;
                  acessoMenuVagas = 1;
                }
                else erro(2); // a[fun��o l� em baixo]

           break; //a[coloquei uns breaks]

            //**Cadastro de N�meros de Vagas
           case 2:

                if (acessoMenuVagas){//a[s� entra se as ruas j� estiverem cadastradas]
                  for (int i = 0; i < QUANT_RUAS; i++)
                  {
                    printf("\n\tInsira o n�mero de vagas dispon�veis para Rua %s: ", estacionamento[i].nome_rua);
                    scanf("%i",&valida); getchar();
                    if (valida<5 || valida>20){
                        i--;
                        erro(9);
                    }else estacionamento[i].num_vagas = valida;
                  }

                  printf("\n\nVagas cadastradas com sucesso.\nPressione enter para continuar...\n");
                  getchar();
                  vagasOK = 1;
                  acessoMenuVagas = 0;
                  acessoMenuValor = 1;
                }
                else{
                  if (!ruasOK) erro(3);
                  else if (vagasOK) erro(6);
                }

           break;

           //**Cadastro de Valor de Vagas
           case 3:
                if (acessoMenuValor){
                  for (int i = 0; i < QUANT_RUAS; i++)
                  {
                    printf("\n\t Insira o valor das vagas para 30 minutos na Rua %s:\n\t(Utilize v�rgula para separa��o dos centavos): ", estacionamento[i].nome_rua);
                    scanf("%f",&validaf); getchar();
                    if (validaf<1 || validaf>2){
                        i--;
                        erro(10);
                    }else estacionamento[i].valor = validaf;
                  }
                  printf("\n\nValor cadastrado com sucesso.\nPressione enter para continuar...");
                  getchar();
                  valorOK = 1;
                  acessoMenuValor = 0;
                  acessoUsuario = 1;
                }
                else{
                  if (!ruasOK) erro(3);
                  else if (!vagasOK) erro(4);
                  else if (valorOK) erro(7);
                }

           break;

           //**Estacionar um Carro
           case 4:

                if (acessoUsuario){
                    printf ("\n**************** Estacione seu Carro *****************\n");

                    printf ("\n               Selecione a rua desejada             \n\n");

                    for (int i = 0; i < QUANT_RUAS; i++)
                        printf ("%d. %s\t\t\t.......[%d]\n",i+1,estacionamento[i].nome_rua,i+1);

                    printf("\nDigite a op��o desejada: ");
                    scanf("%d",&valida); getchar();
                    if (valida<1 || valida>3){
                        i--;
                        erro(1);
                    }
                    else{
                        //buscando um valor 0 no vetor carro[i].tempo para cadastrar o carro
                        for (int i = 0; i < QUANT_RUAS*QUANT_VAGAS; i++){
                            if (carro[i].tempo == 0){
                                carroID = i;
                                i = QUANT_RUAS*QUANT_VAGAS*2;
                            }
                        }
                        carro[carroID].ruaID = valida; // guardou a rua aqui OK

                        printf ("\n\tInsira a placa de seu carro [XXX-0000]: ");
                        scanf("%s",carro[carroID].placa); getchar(); // guardou a placa aqui OK

                        printf ("\n\tInsira o tempo em minutos que deseja permanecer: ");
                        scanf("%d",&carro[carroID].tempo); getchar(); // guardou o tempo aqui OK

                        //debug*******************************************
                        printf ("\n\t\t ****DEBUG**** ");
                        printf ("\n\t\t carros cadastrados at� agora: \n");

                        for (int i = 0; i < QUANT_RUAS*QUANT_VAGAS; i++){
                            if(carro[i].tempo != 0){
                                printf ("\n\t\t rua: %d ", carro[i].ruaID);
                                printf ("\n\t\t placa: %s ", carro[i].placa);
                                printf ("\n\t\t tempo: %d \n", carro[i].tempo);
                                printf ("\n\t\t---%d", i);
                            }
                        }
                        printf ("\n\t\t ****DEBUG**** ");
                        getchar();
                        //debug*******************************************
                    }
                }
                else erro(5);

           break;

           //**Liberar Vaga
           case 5:

                if (acessoUsuario){
                  printf("em desenvolvimento");getchar();
                  //ELABORA��O DA FUN��O 5
                  //printf("\n\tLiberar vaga: ");
                  //scanf("%i",&escolha);
                }
                else erro(5);

           break;

           //f: 6. Emitir Relat�rio//
           case 6:


                printf ("\n****************** Relat�rio Di�rio ******************\n");

                printf ("\n              Selecione a op��o desejada            \n\n");

                printf ("1. Ruas Cadastradas..................................[1]\n");
                printf ("2. Total de Vagas Dispon�veis por rua................[2]\n");
                printf ("3. Carros Estacionados...............................[3]\n");
                printf ("4. Carros Estacionados por rua.......................[4]\n");
                printf ("5. Custo M�dio por Estacionamento....................[5]\n");
                printf ("6. Definir...........................................[6]\n");
                printf ("7. Definir...........................................[7]\n");
                printf ("Sair.................................................[0]\n\n");

                printf("Digite a op��o desejada: ");
                scanf("%d",&opcaoMenuRelatorio);
                getchar();

                switch(opcaoMenuRelatorio){

                //**Ruas cadastradas
                CLEAR_SCREEN
                case 1:

                    if (acessoUsuario){

                        printf("\n\t1. Ruas Cadastradas -----------------------------\n");

                        for (int i = 0; i < QUANT_RUAS; i++)
                        {
                          for (int i = 0; i < QUANT_RUAS; i++)
                          printf("\n\t%s", estacionamento[i].nome_rua);
                          getchar();
                        }
                    }

                    else erro(8);

                break;

                //**Total de Vagas Dispon�veis por rua
                case 2:

                    if (acessoUsuario){

                        printf("\n\t2. Total de Vagas Dispon�veis por Rua ------------\n");

                        for (int i = 0; i < QUANT_RUAS; i++)
                        {
                          for (int i = 0; i < QUANT_RUAS; i++)
                          printf("\n\tRua %s | N�mero de Vagas Dispon�veis: %d\n", estacionamento[i].nome_rua, estacionamento[i].num_vagas);
                          getchar();
                        }
                    }

                    else erro(8);

                break;

                //**Carros Estacionados
                case 3:
                        printf("em desenvolvimento");getchar();
                      //Carros Estacionados por rua//


                    else erro(8);

                break;

                case 4:
                    printf("em desenvolvimento");getchar();
                      //Carros Estacionados por rua//

                break;

                //**Custo M�dio por Estacionamento
                case 5:
                    printf("em desenvolvimento");getchar();
                      //Custo M�dio por Estacionamento//

                break;

                case 6:
                    printf("em desenvolvimento");getchar();
                      //Definir//

                case 7:
                    printf("em desenvolvimento");getchar();
                    //Definir//

                break;

                case 0:
                    printf("\n\tObrigado por utilizar este programa. \n\n");

                break;

            break;
              }//f: Encerra Submenu Relat�rios

        case 0:

        printf("\n\tObrigado por utilizar este programa. At� a pr�xima!\n\n");

        }

    } while(opcaoMenu!=0);

    return 0;
}

/*
Arquivo com fun��o de tratamento de erros.
*/

# include<stdio.h>

//void erro (int codErro, int rua, int vaga, int valor){ //rascunho
void erro (int codErro){
  // a[essa fun��o vai imprimir mensagens de erro, qq d�vida � s� me falar, ok?]

  switch(codErro){

    case 1: //op��o inv�lida
      printf("\n\n+--------------------------------------+");
      printf(  "\n|            Op��o inv�lida            |");
      printf(  "\n+--------------------------------------+");
      printf(  "\n\nPressione enter para continuar...");
      getchar();
      break;

    case 2: //ruas j� foram cadastradas
      printf("\n\n+--------------------------------------+");
      printf(  "\n|     As ruas j� est�o cadastradas     |");
      printf(  "\n+--------------------------------------+");
      printf(  "\n\nPressione enter para continuar...");
      getchar();
      break;

    case 3: //requer cadastro de ruas
      printf("\n\n+--------------------------------------+");
      printf(  "\n|    � necess�rio cadastrar as ruas    |");
      printf(  "\n+--------------------------------------+");
      printf(  "\n\nPressione enter para continuar...");
      getchar();
      break;

    case 4: //requer cadastro de ruas e valores
      printf("\n\n+--------------------------------------+");
      printf(  "\n|   � necess�rio cadastrar as vagas    |");
      printf(  "\n+--------------------------------------+");
      printf(  "\n\nPressione enter para continuar...");
      getchar();
      break;

    case 5: //requer configura��o inicial (ruas pre�o e vagas)
      printf("\n\n+---------------------------------------+");
      printf(  "\n|  O programa precisa ser configurado   |");
      printf(  "\n+---------------------------------------+");
      printf(  "\n\nPressione enter para continuar...");
      getchar();
      break;

    case 6: //vagas j� foram cadastradas
      printf("\n\n+---------------------------------------+");
      printf(  "\n|      Voc� j� cadastrou as vagas       |");
      printf(  "\n+---------------------------------------+");
      printf(  "\n\nPressione enter para continuar...");
      getchar();
      break;

    case 7: //valores j� foram cadastrados
      printf("\n\n+---------------------------------------+");
      printf(  "\n|     Voc� j� cadastrou os valores      |");
      printf(  "\n+---------------------------------------+");
      printf(  "\n\nPressione enter para continuar...");
      getchar();
      break;

    case 8: //Dados n�o encontrados. - Relat�rios
      printf("\n\n+---------------------------------------+");
      printf(  "\n|         Dados n�o encontrados         |");
      printf(  "\n+---------------------------------------+");
      printf(  "\n\nPressione enter para continuar...");
      getchar();
      break;

    case 9: //Dados n�o encontrados. - Relat�rios
      printf("\n\n+---------------------------------------------+");
      printf(  "\n|   O n�mero de vagas deve ser entre 5 e 20   |");
      printf(  "\n+---------------------------------------------+");
      printf(  "\n\nPressione enter para continuar...");
      getchar();
      break;

    case 10: //Dados n�o encontrados. - Relat�rios
      printf("\n\n+--------------------------------------------------------+");
      printf(  "\n| O valor para 30 minutos deve ser entre R$1,00 e R$2,00 |");
      printf(  "\n+--------------------------------------------------------+");
      printf(  "\n\nPressione enter para continuar...");
      getchar();
      break;

    case 11: //Dados n�o encontrados. - Relat�rios
      printf("\n\n+----------------------------------------+");
      printf(  "\n| O tempo v�lido � entre 1 e 120 minutos |");
      printf(  "\n+----------------------------------------+");
      printf(  "\n\nPressione enter para continuar...");
      getchar();
      break;
  }
}
