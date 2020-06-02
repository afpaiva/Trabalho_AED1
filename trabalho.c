/*
Fernando, o que eu comentar, vou colocar entre colchetes com um 'a' antes
Ex: a[comentário do André]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define QUANT_RUAS 3 //f[QUANTIDADE DE RUAS]

void erro(int codErro, int rua, int vaga, int valor);

typedef struct {
  char nome_rua[50];
  int num_vagas;
  int status_vagas[20];
  float valor;
  } ruas;

int main (){

    setlocale (LC_ALL, "Portuguese");

    int opcaoMenu, i, escolha, opcaoMenuRelatorio;
    int acessoMenuRuas = 1, acessoMenuVagas = 0, acessoMenuValor = 0, acessoUsuario = 0;
    //a[variáveis "acesso..." controlam os acessos ao menu, são booleanas]
    int ruasOK = 0, vagasOK = 0, valorOK = 0;
    //a[variaveis "OK" para saber o que já foi entrado]
    ruas estacionamento[QUANT_RUAS];

    do{

        printf ("\n+----------------------------------------------+\n|      Sistema de Estacionamento Rotativo      |\n+----------------------------------------------+\n");

        printf ("\n       ***** Menu *****               \n");
        printf ("\n     Selecione a opção desejada     \n\n");

        if (acessoMenuRuas)
          printf ("Cadastrar Ruas..................[1]\n");
          else
          printf ("Cadastrar Ruas..................[-]\n");

        if (acessoMenuVagas)
          printf ("Cadastro de Números de Vagas....[2]\n");
          else
          printf ("Cadastro de Números de Vagas....[-]\n");

        if (acessoMenuValor)
          printf ("Cadastro de Valor de Vagas......[3]\n");
          else
          printf ("Cadastro de Valor de Vagas......[-]\n");

        if (acessoUsuario){
          printf ("Estacionar um Carro.............[4]\n");
          printf ("Liberar Vaga....................[5]\n");
          printf ("Emitir Relatório................[6]\n");
        }else{
          printf ("Estacionar um Carro.............[-]\n");
          printf ("Liberar Vaga....................[-]\n");
          printf ("Emitir Relatório................[-]\n");
        }

        printf ("Sair..............................[0]\n\n");


        printf("Digite a opção desejada: ");
        scanf("%i",&opcaoMenu);
        getchar(); //a[coloquei um getchar aqui]

        if (opcaoMenu<0 || opcaoMenu>6) erro(1, ruasOK, vagasOK, valorOK); // a[erro é uma função lá em baixo]

        switch(opcaoMenu){

            case 1:

            if (acessoMenuRuas){
              for (int i = 0; i < QUANT_RUAS; i++)
              {
                printf("\n\tInsira o nome da %iª rua a ser cadastrada: ",i+1);
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
            else erro(2, ruasOK, vagasOK, valorOK); // a[função lá em baixo]

            break; //a[coloquei uns breaks]

           case 2:

            if (acessoMenuVagas){//a[só entra se as ruas já estiverem cadastradas]
              for (int i = 0; i < QUANT_RUAS; i++)
              {
                printf("\n\tInsira o número de vagas disponíveis para Rua %s: ", estacionamento[i].nome_rua);
                scanf("%i",&estacionamento[i].num_vagas); getchar();
              }
              printf("\n\nVagas cadastradas com sucesso.\nPressione enter para continuar...\n");
              getchar();
              vagasOK = 1;
              acessoMenuVagas = 0;
              acessoMenuValor = 1;
            }
            else{
              if (!ruasOK) erro(3, ruasOK, vagasOK, valorOK);
              else if (vagasOK) erro(6, ruasOK, vagasOK, valorOK);
            }

           break;

           case 3:
            if (acessoMenuValor){
              for (int i = 0; i < QUANT_RUAS; i++)
              {
                printf("\n\tInsira o valor das vagas da Rua %s: ", estacionamento[i].nome_rua);
                scanf("%f",&estacionamento[i].valor); getchar();
              }
              printf("\n\nValores cadastrados com sucesso.\nPressione enter para continuar...");
              getchar();
              valorOK = 1;
              acessoMenuValor = 0;
              acessoUsuario = 1;
            }
            else{
              if (!ruasOK) erro(3, ruasOK, vagasOK, valorOK);
              else if (!vagasOK) erro(4, ruasOK, vagasOK, valorOK);
              else if (valorOK) erro(7, ruasOK, vagasOK, valorOK);
            }

           break;

           case 4:

            if (acessoUsuario){
              printf("em desenvolvimento");getchar();
              //ELABORAÇÃO DA FUNÇÃO 4
              //printf("\n\tInsira a opção desejada: ");
              //scanf("%i",&escolha);
            }
            else erro(5, ruasOK, vagasOK, valorOK);

           break;

           case 5:

            if (acessoUsuario){
              printf("em desenvolvimento");getchar();
              //ELABORAÇÃO DA FUNÇÃO 5
              //printf("\n\tLiberar vaga: ");
              //scanf("%i",&escolha);
            }
            else erro(5, ruasOK, vagasOK, valorOK);

           break;

           //f: 6. Emitir Relatório//
           case 6:

            printf ("\n****************** Relatório Diário ******************\n");

            printf ("\n              Selecione a opção desejada            \n\n");

                  printf ("1. Ruas Cadastradas..................................[1]\n");
                  printf ("2. Total de Vagas Disponíveis por rua................[2]\n");
                  printf ("3. Carros Estacionados...............................[3]\n");
                  printf ("4. Carros Estacionados por rua.......................[4]\n");
                  printf ("5. Custo Médio por Estacionamento....................[5]\n");
                  printf ("6. Definir...........................................[6]\n");
                  printf ("7. Definir...........................................[7]\n");
                  printf ("Sair.................................................[0]\n\n");

        printf("Digite a opção desejada: ");
        scanf("%d",&opcaoMenuRelatorio);
        getchar();

        switch(opcaoMenuRelatorio){

            case 1:

        if (acessoUsuario){

                printf("\n\t1. Ruas Cadastradas ---------------------\n");

            for (int i = 0; i < QUANT_RUAS; i++)
              {
                  printf("\n\t%s", estacionamento[i].nome_rua);
                  getchar();
                }
                   }

        else erro(8, ruasOK, vagasOK, valorOK);

           break;

           case 2:
                printf("em desenvolvimento");getchar();
                //Total de Vagas Disponíveis por rua//

            break;

            case 3:
                printf("em desenvolvimento");getchar();
                  //Carros Estacionados//

            break;

            case 4:
                printf("em desenvolvimento");getchar();
                  //Carros Estacionados por rua//

            break;

           case 5:
                printf("em desenvolvimento");getchar();
                  //Custo Médio por Estacionamento//

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

              }//f: Encerra Submenu Relatórios

           case 0:

           printf("\n\tObrigado por utilizar este programa. Até a próxima!\n\n");

        }

    } while(opcaoMenu!=0);

    return 0;
}

void erro (codErro, rua, vaga, valor){
  // a[essa função vai imprimir mensagens de erro, qq dúvida é só me falar, ok?]

  switch(codErro){

    case 1: //opção inválida
      printf("\n\n+--------------------------------------+\n|            Opção inválida            |\n+--------------------------------------+\n\nPressione enter para continuar..."); getchar();
      break;

    case 2: //ruas já foram cadastradas
      printf("\n\n+--------------------------------------+\n|     As ruas já estão cadastradas     |\n+--------------------------------------+\n\nPressione enter para continuar..."); getchar();
      break;

    case 3: //requer cadastro de ruas
      printf("\n\n+--------------------------------------+\n|    É necessário cadastrar as ruas    |\n+--------------------------------------+\n\nEntre com opção 1 no menu inicial.\nPressione enter para continuar..."); getchar();
      break;

    case 4: //requer cadastro de ruas e valores
      printf("\n\n+---------------------------------------+\n|    É necessário cadastrar as vagas    |\n+---------------------------------------+\n\nEntre com opção 2 no menu inicial.\nPressione enter para continuar..."); getchar();
      break;

    case 5: //requer configuração inicial (ruas preço e vagas)
      printf("\n\n+--------------------------------------+\n|  O programa precisa ser configurado  |\n+--------------------------------------+\n\nCadastre:");
      if (!rua) printf("\n\t-> as ruas;");
      if (!vaga) printf("\n\t-> as vagas;");
      if (!valor) printf("\n\t-> os valores;");
      printf("\n\tNo menu inicial.\n\nPressione enter para continuar..."); getchar();
      break;

    case 6: //vagas já foram cadastradas
      printf("\n\n+--------------------------------------+\n|      Você já cadastrou as vagas      |\n+--------------------------------------+\n\nPressione enter para continuar..."); getchar();
      break;

    case 7: //valores já foram cadastrados
      printf("\n\n+--------------------------------------+\n|     Você já cadastrou os valores     |\n+--------------------------------------+\n\nPressione enter para continuar..."); getchar();
      break;

    case 8: //Dados não encontrados. - Relatórios
      printf("\n\n+--------------------------------------+\n|         Dados não encontrados        |\n+--------------------------------------+\n\nPressione enter para continuar..."); getchar();
      break;

  }

}
