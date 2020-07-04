/*Projeto final - Controle de vagas de estacionamento | Fase 2
Professor: Claudio Correa e Luiz Gomes
Dupla: André Fonseca de Paiva e Fernando Thales Pereira
Úlltima atualização: 17/06/2020 */

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
#define LIMITE_CARROS 1000 //quantidade máxima de carros no histórico

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
    int tempo;
    int ruaID;
    int vaga;
} carros;

int main (){

    setlocale (LC_ALL, "Portuguese");

    int opcaoMenu, i, escolha, opcaoMenuRelatorio;
    int acessoMenuRuas = 1, acessoMenuVagas = 0, acessoMenuValor = 0, acessoUsuario = 0;
    //variáveis "acesso..." controlam os acessos ao menu, são booleanas
    int ruasOK = 0, vagasOK = 0, valorOK = 0;
    //variaveis "OK" para saber o que já foi entrado
    ruas estacionamento[QUANT_RUAS];
    int valida, validaB, cont = 0; // a2[Para validações em geral]
    float validaf, mediaValorRua = 0; // a2[Para validações em geral]
    int rua_escolhida; // registra temporariamente a rua escolhida
    carros carro[QUANT_VAGAS*QUANT_RUAS]; // struct carros com total de vagas disponiveis
    int carroID, carroHistID = 0; // guarda provisoriamente o carro que está sendo tratado
    int menuRelatorio = 1; // 1 mostra menu relatório, 0 volta menu inicial
    carros carroHistorico[LIMITE_CARROS];

    for (int i = 0; i < LIMITE_CARROS; i++)
        carroHistorico[i].tempo = 0;

    //zerando os tempos das vagas para facilitar no relatório depois
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
        }else{
          printf ("Estacionar um Carro.............[-]\n");
          printf ("Liberar Vaga....................[-]\n");
        }

        printf ("Emitir Relatório................[6]\n");
        printf ("Sair............................[0]\n\n");


        printf("Digite a opção desejada: ");
        scanf("%i",&opcaoMenu);
        getchar(); //a[coloquei um getchar aqui]

        if (opcaoMenu<0 || opcaoMenu>6) erro(1); // a[erro é uma função lá em baixo]

        switch(opcaoMenu){
            case 1://**Cadastrar Ruas
                if (acessoMenuRuas){
                  for (int i = 0; i < QUANT_RUAS; i++)
                  {
                    printf("\n\tInsira o nome da %iª rua a ser cadastrada: ",i+1);
                    scanf("%[^\n]s",estacionamento[i].nome_rua);
                    getchar();
                    // a[Cadastro de ruas OK!]
                  }
                  printf("\n\nRuas cadastradas com sucesso.\nPressione [Enter] para continuar...\n");
                  getchar();
                  ruasOK = 1;
                  acessoMenuRuas = 0;
                  acessoMenuVagas = 1;
                }
                else erro(2);
           break;

           case 2: //**Cadastro de Números de Vagas
                if (acessoMenuVagas){//a[só entra se as ruas já estiverem cadastradas]
                  for (int i = 0; i < QUANT_RUAS; i++)
                  {
                    printf("\n\tInsira o número de vagas disponíveis para Rua %s: ", estacionamento[i].nome_rua);
                    scanf("%i",&valida); getchar();
                    if (valida<5 || valida>20){
                        i--;
                        erro(9);
                    }else estacionamento[i].num_vagas = valida;
                  }
                  printf("\n\nVagas cadastradas com sucesso.\nPressione [Enter] para continuar...\n");
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

           case 3: //**Cadastro de Valor de Vagas
                if (acessoMenuValor){
                  for (int i = 0; i < QUANT_RUAS; i++)
                  {
                    printf("\n\t Insira o valor das vagas para 30 minutos na Rua %s:\n\t(Utilize vírgula para separação dos centavos): ", estacionamento[i].nome_rua);
                    scanf("%f",&validaf); getchar();
                    if (validaf<1 || validaf>2){
                        i--;
                        erro(10);
                    }else estacionamento[i].valor = validaf;
                  }
                  printf("\n\nValor cadastrado com sucesso.\nPressione [Enter] para continuar...");
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

           case 4: //**Estacionar um Carro
                if (acessoUsuario){
                    printf ("\n**************** Estacione seu Carro *****************\n");
                    printf ("\n               Selecione a rua desejada             \n\n");

                    for (int i = 0; i < QUANT_RUAS; i++)
                        printf ("%d. %s\t\t\t.......[%d]\n",i+1,estacionamento[i].nome_rua,i+1);

                    printf("\nDigite a opção desejada: ");
                    scanf("%d",&valida); getchar();
                    if (valida<1 || valida>3){
                        erro(1);
                    }
                    else{
                        valida --;
                        //buscando um valor 0 no vetor carro[i].tempo para cadastrar o carro
                        for (int i = 0; i < QUANT_RUAS*QUANT_VAGAS; i++){
                            if (carro[i].tempo == 0){
                                carroID = i;
                                i = QUANT_RUAS*QUANT_VAGAS*2;
                            }
                        }
                        carro[carroID].ruaID = valida; // guardou a rua aqui OK
                        carroHistorico[carroHistID].ruaID = valida; // historico para relatorio

                        printf ("\n\tInsira a placa de seu carro [XXX-0000]: ");
                        scanf("%s",carro[carroID].placa); getchar(); // guardou a placa aqui OK
                        strcpy(carroHistorico[carroHistID].placa,carro[carroID].placa);
                        // historico para relatorio

                        printf ("\n\tInsira o tempo em minutos que deseja permanecer: ");
                        scanf("%d",&carro[carroID].tempo); getchar(); // guardou o tempo aqui OK
                        carroHistorico[carroHistID].tempo = carro[carroID].tempo; // historico para relatorio

                        for (int i = 0; i < QUANT_VAGAS; i++){
                            if (estacionamento[valida].status_vagas[i] == 0){
                                estacionamento[valida].status_vagas[i] = 1;
                                carro[carroID].vaga = i;
                                carroHistorico[carroHistID].vaga = i;
                                i = QUANT_VAGAS*2;
                            }
                        }
                        carroHistID++;
                    }
                }
                else erro(5);
           break;

           case 5: //**Liberar Vaga

                if (acessoUsuario){
                  printf ("\n**************** Liberar Vaga *****************\n\n");

                    cont = 0;
                    valida = 0;
                    for (int i = 0; i < QUANT_RUAS; i++){
                        for (int j = 0; j < estacionamento[i].num_vagas; j++)
                            if (estacionamento[i].status_vagas[j] == 1){
                                valida = 1;
                                cont++;
                            }
                        if (valida == 1)
                            printf ("%d. Rua %s\t\t\t.......[%d]\n",i+1,estacionamento[i].nome_rua,i+1);
                    }
                    if (cont == 0){
                        printf ("\n\nTodas as vagas estão livres\n\nPressione [Enter] para voltar.......");
                        getchar();
                        break;
                    }

                    printf("\nDigite a opção desejada ou (0) para retornar: ");
                    scanf("%d",&valida); getchar();

                    if (valida != 0){
                        valida--;
                        printf("\nVagas ocupadas para Rua %s: \n", estacionamento[valida].nome_rua);
                        for (int i = 0; i < estacionamento[valida].num_vagas;i++){
                            if (estacionamento[valida].status_vagas[i] == 1)
                                printf ("\tVaga R%d-V%d........[%d]\n",valida+1,i+1,i+1);
                        }
                        printf("\nEntre com a opção correspondente para liberar a vaga ou (0) para retornar: ");
                        scanf("%d",&validaB); getchar();

                        if (validaB != 0){
                            validaB --;
                            estacionamento[valida].status_vagas[validaB] = 0;
                            for (i = 0; i < QUANT_RUAS*QUANT_VAGAS; i++){
                                if (carro[i].ruaID == valida && carro[i].vaga == validaB){
                                    carro[i].vaga = -1;
                                    carro[i].tempo = 0;
                                    carro[i].ruaID = -1;
                                }
                            }
                        }
                        else { break; }
                    }
                    else { break; }
                    printf("\nVaga liberada. Pressione [Enter] para continuar..." );
                    getchar();
                }
                else erro(5);
           break;

           case 6: //f: 6. Emitir Relatório//
                do{
                    CLEAR_SCREEN
                    printf ("\n****************** Relatório Diário ******************\n");
                    printf ("\n              Selecione a opção desejada            \n\n");
                    printf ("1. Ruas Cadastradas..................................[1]\n");
                    printf ("2. Total de Vagas Disponíveis por rua................[2]\n");
                    printf ("3. Carros Estacionados...............................[3]\n");
                    printf ("4. Carros Estacionados por rua.......................[4]\n");
                    printf ("5. Custo Médio por Estacionamento....................[5]\n");
                    printf ("6. Valor de Vaga - Ruas Cadastradas..................[6]\n");
                    printf ("7. Relatório de Estacionamentos Efetivados...........[7]\n");
                    printf ("Voltar...............................................[0]\n\n");

                    printf("Digite a opção desejada: ");
                    scanf("%d",&opcaoMenuRelatorio);
                    getchar();

                    if (opcaoMenuRelatorio<0 || opcaoMenuRelatorio>7) erro(1);

                    switch(opcaoMenuRelatorio){
                    case 1: //1. Ruas cadastradas
                        if (ruasOK){
                            printf("\n\t1. Ruas Cadastradas -----------------------------\n");

                            for (int i = 0; i < QUANT_RUAS; i++)
                            {
                              printf("\n\tRua %s", estacionamento[i].nome_rua);
                            }
                            printf("\n\nPressione [Enter] para continuar...");
                            getchar();
                        }
                        else erro(8);
                    break;

                    case 2: //2. Total de Vagas Disponíveis por rua
                        if (vagasOK){
                            cont = 0;
                            printf("\n\t2. Total de Vagas Disponíveis por Rua ------------\n");
                            //subtrair vagas já ocupadas
                            for (int i = 0; i < QUANT_RUAS; i++)
                            {
                                for (int j = 0; j < estacionamento[i].num_vagas; j++)
                                    if (estacionamento[i].status_vagas[j] == 1)
                                        cont++;

                                printf("\n\tRua %s | Número de Vagas Disponíveis: %d de %d\n"
                                   , estacionamento[i].nome_rua
                                   , estacionamento[i].num_vagas-cont
                                   , estacionamento[i].num_vagas);
                                cont = 0;
                            }
                            printf(  "\n\nPressione [Enter] para continuar...");
                            getchar();
                        }
                        else erro(8);
                    break;

                    case 3: //3. Carros Estacionados
                        if (acessoUsuario){
                            printf("\n\t3. Carros Estacionados ------------------------------\n");
                            cont = 0;
                            for (int i = 0; i < QUANT_RUAS; i++){
                                for (int j = 0; j < QUANT_RUAS*QUANT_VAGAS; j++)
                                    if (carro[j].tempo != 0 && carro[j].ruaID == i) {
                                        printf ("\n\t\t\t Placa: %s",   carro[j].placa);
                                        printf ("\n\t\t\t Código da vaga: R%d-V%d",  i+1 , carro[j].vaga);
                                        printf ("\n\t\t\t Tempo: %d\n", carro[j].tempo);
                                        cont++;
                                    }
                                }
                            if (cont == 0) printf ("\n\t\t-Não há carros estacionados.\n");

                            printf(  "\n\nPressione [Enter] para continuar...");
                            getchar();
                        }
                        else erro(8);
                    break;

                    //4. Carros Estacionados por rua//
                    case 4:
                         if (acessoUsuario){
                            printf("\n\t4. Carros Estacionados por Rua ----------------------\n");
                            cont = 0;
                            for (int i = 0; i < QUANT_RUAS; i++){
                                printf ("\n\n\t\tRua %s: ", estacionamento[i].nome_rua);
                                for (int j = 0; j < QUANT_RUAS*QUANT_VAGAS; j++)
                                    if (carro[j].tempo != 0 && carro[j].ruaID == i) {
                                        printf ("\n\t\t\t Placa: %s", carro[j].placa);
                                        cont++;
                                    }
                                if (cont == 0) printf ("\n\t\t-Não há carros estacionados nesta rua.\n");
                            }
                            printf(  "\n\nPressione [Enter] para continuar...");
                            getchar();
                        }
                        else erro(8);
                    break;

                    case 5: //5. Custo Médio por Estacionamento
                        if (valorOK){
                            valida = 0;
                            validaf = 0.0;
                            printf("\n\t4. Custo Médio por Estacionamento ----------------------\n");
                            for (int i = 0; i < QUANT_RUAS; i++){
                                validaf = estacionamento[i].valor * estacionamento[i].num_vagas;
                                valida += estacionamento[i].num_vagas;
                                mediaValorRua += validaf;
                            }
                            mediaValorRua = mediaValorRua / valida;
                            printf ("\n\n\tA média do valor das vagas é de R$ %.2f: ", mediaValorRua);
                            printf(  "\n\nPressione [Enter] para continuar...");
                            getchar();
                        }
                        else erro(8);
                        break;

                    case 6: //6. Valor de Vaga - Ruas Cadastradas
                        if (valorOK){
                            printf("\n\6. Valor Vaga (30 min) - Ruas Cadastradas ----------------------\n");

                            for (int i = 0; i < QUANT_RUAS; i++){
                                printf ("\n\t\t Rua %s: R$ %.2f", estacionamento[i].nome_rua, estacionamento[i].valor);
                            }
                            printf(  "\n\nPressione [Enter] para continuar...");
                            getchar();
                        }
                        else erro(8);
                        break;

                    case 7: //7. Relatório de Estacionamentos Efetivados
                        if (acessoUsuario) {
                            printf("\n\7. Relatório de Estacionamentos Efetivados ----------------------\n");

                            printf ("\n\t Carros que utilizaram nosso estacionamento: \n");

                            for (int i = 0; i <= carroHistID; i++)
                            {
                                if (carroHistorico[i].tempo != 0){
                                    printf ("\n\t\t Veículo com placa %s: ", carroHistorico[i].placa);
                                    printf ("\n\t\t Permaneceu por %d minutos.", carroHistorico[i].tempo);
                                    printf ("\n\t\t Estacionou na vaga código: R%dV%d.", carroHistorico[i].ruaID,carroHistorico[i].vaga);
                                    printf ("\n\t\t Situada na rua %s.\n", estacionamento[carroHistorico[i].ruaID].nome_rua);
                                }
                            }
                            printf(  "\n\nPressione [Enter] para continuar...");
                            getchar();
                        }
                        else erro(8);
                        break;
                    }
                } while (opcaoMenuRelatorio != 0);
            break;

        case 0: //f: Encerra Submenu Relatórios
            printf("\n\tObrigado por utilizar este programa. Até a próxima!\n\n");
        }
    } while(opcaoMenu!=0);

    return 0;
}

//void erro (int codErro, int rua, int vaga, int valor){ //rascunho
void erro (int codErro){
  // a[essa função vai imprimir mensagens de erro, qq dúvida é só me falar, ok?]

  switch(codErro){

    case 1: //opção inválida
      printf("\n\n+--------------------------------------+");
      printf(  "\n|            Opção inválida            |");
      printf(  "\n+--------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 2: //ruas já foram cadastradas
      printf("\n\n+--------------------------------------+");
      printf(  "\n|     As ruas já estão cadastradas     |");
      printf(  "\n+--------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 3: //requer cadastro de ruas
      printf("\n\n+--------------------------------------+");
      printf(  "\n|    É necessário cadastrar as ruas    |");
      printf(  "\n+--------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 4: //requer cadastro de ruas e valores
      printf("\n\n+--------------------------------------+");
      printf(  "\n|   É necessário cadastrar as vagas    |");
      printf(  "\n+--------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 5: //requer configuração inicial (ruas preço e vagas)
      printf("\n\n+---------------------------------------+");
      printf(  "\n|  O programa precisa ser configurado   |");
      printf(  "\n+---------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 6: //vagas já foram cadastradas
      printf("\n\n+---------------------------------------+");
      printf(  "\n|      Você já cadastrou as vagas       |");
      printf(  "\n+---------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 7: //valores já foram cadastrados
      printf("\n\n+---------------------------------------+");
      printf(  "\n|     Você já cadastrou os valores      |");
      printf(  "\n+---------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 8: //Dados não encontrados. - Relatórios
      printf("\n\n+---------------------------------------+");
      printf(  "\n|         Dados não encontrados         |");
      printf(  "\n+---------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 9: //Dados não encontrados. - Relatórios
      printf("\n\n+---------------------------------------------+");
      printf(  "\n|   O número de vagas deve ser entre 5 e 20   |");
      printf(  "\n+---------------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 10: //Dados não encontrados. - Relatórios
      printf("\n\n+--------------------------------------------------------+");
      printf(  "\n| O valor para 30 minutos deve ser entre R$1,00 e R$2,00 |");
      printf(  "\n+--------------------------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 11: //Dados não encontrados. - Relatórios
      printf("\n\n+----------------------------------------+");
      printf(  "\n| O tempo válido é entre 1 e 120 minutos |");
      printf(  "\n+----------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;
  }
}
