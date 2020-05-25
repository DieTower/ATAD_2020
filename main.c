/* PROJETO  ATAD 2019-20
* Identificacao dos Alunos:
*
*      Numero: 190221118 | Nome: Nicole Alexandra Martins Vieira
*      Numero: 190221125 | Nome: Rodrigo Nave da Costa
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "utils.h"
//#include "list.h"

typedef char String[255];

/* definicao de prototipos de funcoes, definidas depois do main() */
int equalsStringIgnoreCase(char str1[], char str2[]);
void printCommandsMenu();
//...

/*
* Descrição do Programa
*/
int main(int argc, char** argv) {

	// PtList kahootList = listCreate(1024);

    // importKahootReportsFromFile("kahootReports.csv", &kahootList);
    // listPrint(kahootList);
    // PtListKahootReportDestroy(kahootList);

	/* declaracao de variaveis */
	PtList list = listCreate(1024);
	importPatientsFromFile("patients.csv", &list);
	listPrint(list);
	listDestroy(&list);


	/* interpretador de comandos */
	String command;
	int quit = 0;

	setlocale(LC_ALL, "PT");
	while (!quit) {
		
		printCommandsMenu();
		fgets(command, sizeof(command), stdin);
		/* descartar 'newline'. Utilizar esta técnica sempre que for lida uma
		* string para ser utilizada, e.g., nome de ficheiro, chave, etc.. */
		command[strlen(command) - 1] = '\0';
        
		if (equalsStringIgnoreCase(command, "QUIT")) {
			quit = 1; /* vai provocar a saída do interpretador */				
		}
		else if (equalsStringIgnoreCase(command, "LOAD")) {
			/* invocação da função responsável pela respetiva
			funcionalidade. Remover printf seguinte após implementação */
			printf("Comando LOAD nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "LOADR")) {
			/* invocação da função responsável pela respetiva
			funcionalidade. Remover printf seguinte após implementação */
			printf("Comando LOADR nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "CLEAR")) {
			printf("Comando CLEAR nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "AVERAGE")) {
			printf("Comando AVERAGE nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "FOLLOW")) {
			printf("Comando FOLLOW nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "SEX")) {
			printf("Comando SEX nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "SHOW")) {
			printf("Comando SHOW nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "TOP5")) {
			printf("Comando TOP5 nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "OLDEST")) {
			printf("Comando OLDEST nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "GROWTH")) {
			printf("Comando GROWTH nao implementado.\n");
		}	
		else if (equalsStringIgnoreCase(command, "MATRIX")) {
			printf("Comando MATRIX nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "REGIONS")) {
			printf("Comando REGIONS nao implementado.\n");
		}	
		else if (equalsStringIgnoreCase(command, "REPORT")) {
			printf("Comando REPORT nao implementado.\n");
		}
		else {
			printf("%s : Comando não encontrado.\n", command);
		}
	}

	/* libertar memória e apresentar mensagem de saída. */

	return (EXIT_SUCCESS);
}

int equalsStringIgnoreCase(char str1[], char str2[]) {
	upperCase(str1);
	return (strcmp(str1, str2) == 0);
}

void printCommandsMenu() {
	printf("\n===================================================================================");
	printf("\n                          PROJECT: COVID-19                    ");
	printf("\n===================================================================================");
	printf("\nA. Base Commands (LOAD, LOADR,CLEAR).");
	printf("\nB. Simple Indicators and searchs (AVERAGE, FOLLOW, MATRIX, OLDEST, RELEASED, SEX, SHOW, TOP5).");
	printf("\nC. Advanced indicator (REGIONS, REPORTS)");
	printf("\nD. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}
