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

			patientList = listCreate(1024);
			regionMap = mapCreate(1024);

			printf("%d records deleted from <Patients | Regions>\n", (patientSize + regionSize));
		}
		else if (equalsStringIgnoreCase(command, "AVERAGE")) {
			patientsAVG(patientList, "deceased");
			patientsAVG(patientList, "released");
			patientsAVG(patientList, "isolated");
		}
		else if (equalsStringIgnoreCase(command, "FOLLOW")) {
			
			String id;

			printf("PATIENT ID> ");
			fgets(id, sizeof(id), stdin);
			id[strlen(id) - 1] = '\0';
			
			patientsFOLLOW(patientList, atol(id)); // Ex.: 1000000005
			printf("\n");
		}
		else if (equalsStringIgnoreCase(command, "SEX")) {
			
			patientsSEX(patientList, "female");
			patientsSEX(patientList, "male");
			patientsSEX(patientList, "unknown");
		}
		else if (equalsStringIgnoreCase(command, "SHOW")) {
			
			String id;

			printf("PATIENT ID> ");
			fgets(id, sizeof(id), stdin);
			id[strlen(id) - 1] = '\0';
			
			printf("\n");
			patientsSHOW(patientList, atol(id)); // Ex.: 1000000482
		}
		else if (equalsStringIgnoreCase(command, "TOP5")) {
			patientsTOP5(patientList);
		}
		else if (equalsStringIgnoreCase(command, "OLDEST")) {
			patientsOLDEST(patientList);
		}
		else if (equalsStringIgnoreCase(command, "GROWTH")) {
			String day, month, year;

			printf("Please insert a date\n");
			printf("DAY >");
			fgets(day, sizeof(day), stdin);
			day[strlen(day) - 1] = '\0';
			
			printf("MONTH >");
			fgets(month, sizeof(month), stdin);
			month[strlen(month) - 1] = '\0';

			printf("YEAR >");
			fgets(year, sizeof(year), stdin);
			year[strlen(year) - 1] = '\0';

			PtDate dateFormat = dateCreate(atol(day), atol(month), atol(year));

			printf("\n");
			patientsGROWTH(patientList, dateFormat);
		}	
		else if (equalsStringIgnoreCase(command, "MATRIX")) {
			patientsMATRIX(patientList);
		}
		else if (equalsStringIgnoreCase(command, "REGIONS")) {
			patientsREGIONS(patientList, regionMap);
		}	
		else if (equalsStringIgnoreCase(command, "REPORT")) {
			printf("Comando REPORT nao implementado.\n");
		}
		else {
			printf("%s : Comando não encontrado.\n", command);
		}
	}

	/* libertar memória e apresentar mensagem de saída. */
	listDestroy(&patientList);
	mapDestroy(&regionMap);

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
	printf("\nB. Simple Indicators and searchs (AVERAGE, FOLLOW, SEX, SHOW, TOP5, OLDEST, GROWTH, MATRIX).");
	printf("\nC. Advanced indicator (REGIONS, REPORTS)");
	printf("\nD. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}
