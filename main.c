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
#include "map.h"

typedef char String[255];

/* definicao de prototipos de funcoes, definidas depois do main() */
int equalsStringIgnoreCase(char str1[], char str2[]);
void printCommandsMenu();
//...

/*
* Descrição do Programa
*/
int main(int argc, char** argv) {

	// PtMap mapList = mapCreate(1024);
	
	// importRegionsFromFile("regions.csv", &mapList);
	// mapPrint(mapList);

	// mapDestroy(&mapList);

	// PtList list = listCreate(1024);
	// importPatientsFromFile("patients.csv", &list);
	// listPrint(list);
	// listDestroy(&list);

	/* declaracao de variaveis */
	PtList patientList = listCreate(1024);
	PtMap regionMap = mapCreate(1024);

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
		else if (equalsStringIgnoreCase(command, "LOADP")) {
			
			// --- Load patients file ---

			String fileName;

			printf("FILENAME> ");
			fgets(fileName, sizeof(fileName), stdin);
			fileName[strlen(fileName) - 1] = '\0';

			importPatientsFromFile(fileName, &patientList); // -> patients.csv
		}
		else if (equalsStringIgnoreCase(command, "LOADR")) {

			// --- Load region file ---

			importRegionsFromFile("regions.csv", &regionMap);
		}
		else if (equalsStringIgnoreCase(command, "CLEAR")) {

			// --- Clear data ---

			// Patient list and Region map sizes
			int patientSize = 0;
			listSize(patientList, &patientSize);

			int regionSize = 0;
			mapSize(regionMap, &regionSize);
			
			// Destroy patient list and region map
			listDestroy(&patientList);
			mapDestroy(&regionMap);

			printf("%d records deleted from <Patients | Regions>\n", (patientSize + regionSize));
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
	char strCmp[50] = " ";
	upperCase(str1, strCmp);
	return (strcmp(strCmp, str2) == 0);
}

void printCommandsMenu() {
	printf("\n===================================================================================");
	printf("\n                          PROJECT: COVID-19                    ");
	printf("\n===================================================================================");
	printf("\nA. Base Commands (LOADP, LOADR, CLEAR).");
	printf("\nB. Simple Indicators and searchs (AVERAGE, FOLLOW, MATRIX, OLDEST, RELEASED, SEX, SHOW, TOP5).");
	printf("\nC. Advanced indicator (REGIONS, REPORTS)");
	printf("\nD. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}
