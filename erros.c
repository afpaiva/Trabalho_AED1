/*
ARQUIVO DE FUNÇÃO PARA TRATAMENTO DE ERROS
*/

#include <stdio.h>

// Função para tratamento de erros
void erro (int codErro){

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
