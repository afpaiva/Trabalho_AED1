/*
ARQUIVO DE FUN��O PARA TRATAMENTO DE ERROS
*/

#include <stdio.h>

// Fun��o para tratamento de erros
void erro (int codErro){

  switch(codErro){

    case 1: //op��o inv�lida
      printf("\n\n+--------------------------------------+");
      printf(  "\n|            Op��o inv�lida            |");
      printf(  "\n+--------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 2: //ruas j� foram cadastradas
      printf("\n\n+--------------------------------------+");
      printf(  "\n|     As ruas j� est�o cadastradas     |");
      printf(  "\n+--------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 3: //requer cadastro de ruas
      printf("\n\n+--------------------------------------+");
      printf(  "\n|    � necess�rio cadastrar as ruas    |");
      printf(  "\n+--------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 4: //requer cadastro de ruas e valores
      printf("\n\n+--------------------------------------+");
      printf(  "\n|   � necess�rio cadastrar as vagas    |");
      printf(  "\n+--------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 5: //requer configura��o inicial (ruas pre�o e vagas)
      printf("\n\n+---------------------------------------+");
      printf(  "\n|  O programa precisa ser configurado   |");
      printf(  "\n+---------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 6: //vagas j� foram cadastradas
      printf("\n\n+---------------------------------------+");
      printf(  "\n|      Voc� j� cadastrou as vagas       |");
      printf(  "\n+---------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 7: //valores j� foram cadastrados
      printf("\n\n+---------------------------------------+");
      printf(  "\n|     Voc� j� cadastrou os valores      |");
      printf(  "\n+---------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 8: //Dados n�o encontrados. - Relat�rios
      printf("\n\n+---------------------------------------+");
      printf(  "\n|         Dados n�o encontrados         |");
      printf(  "\n+---------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 9: //Dados n�o encontrados. - Relat�rios
      printf("\n\n+---------------------------------------------+");
      printf(  "\n|   O n�mero de vagas deve ser entre 5 e 20   |");
      printf(  "\n+---------------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 10: //Dados n�o encontrados. - Relat�rios
      printf("\n\n+--------------------------------------------------------+");
      printf(  "\n| O valor para 30 minutos deve ser entre R$1,00 e R$2,00 |");
      printf(  "\n+--------------------------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;

    case 11: //Dados n�o encontrados. - Relat�rios
      printf("\n\n+----------------------------------------+");
      printf(  "\n| O tempo v�lido � entre 1 e 120 minutos |");
      printf(  "\n+----------------------------------------+");
      printf(  "\n\nPressione [Enter] para continuar...");
      getchar();
      break;
  }
}
