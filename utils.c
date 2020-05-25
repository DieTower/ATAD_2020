/**
 * @file utils.c
 * @brief Useful code
 * @date 2020-05-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "utils.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void lowerCase(char *str) {
    int size = (int)strlen(str);
    
    for(int i = 0; i < size; i++) {
        str[i] = tolower(str[i]);
    }

    str[size] = '\0';
};

void upperCase(char *str) {
    int size = (int)strlen(str);
    
    for(int i = 0; i < size; i++) {
        str[i] = toupper(str[i]);
    }

    str[size] = '\0';
};

char** split(char *string, int nFields, const char *delim) {

    char **tokens = (char**) malloc(sizeof(char*) * nFields);

    int index = 0;

    int len = strlen(string);

    tokens[index++] = &string[0];

    for(int i=0; i < len; i++) {
        
        if(string[i] == delim[0]) {

            string[i] = '\0';

            if(i < len-1) {

                tokens[index++] = &string[i] + 1;

            }

        }

    }

    return tokens;
};

void importPatientsFromFile(char * filename, PtList *listPatient) {
    FILE *f = NULL;

    f = fopen(filename, "r");

    if(f == NULL) {
        printf("An error ocurred... It wad not possible to open the file %s ...\n", filename);
        return;
    }

    char nextline[1024];

    int countPatient = 0; // patient count
    bool firstLine = true;

    while(fgets(nextline, sizeof(nextline), f)) {
        if(strlen(nextline) < 1)
            continue;

        /* --- As the first line of the file contains the names of the fields ir should be ignored --- */
        if(firstLine) {
            firstLine = false;
            continue;
        }

        char **tokens = split(nextline, 11, ";");
        
        /* --- At this moment the tokens array is composed with the following "strings" --- */
        // tokens[0] = patient_id
        // tokens[1] = sex
        // tokens[2] = birth_year
        // tokens[3] = country
        // tokens[4] = province
        // tokens[5] = infection_case
        // tokens[6] = infected_by
        // tokens[7] = confirmed_date
        // tokens[8] = released_date
        // tokens[9] = deceased_date
        // tokens[10] = state

        /* --- Set dates from patient --- */

        // Patient confirmed date
        PtDate confirmedDate;
        if(strlen(tokens[7]) == 0) {
            confirmedDate = dateCreate(0,0,0);
        } else {
            char **confirmedDateTokens = split(tokens[7], 3, "/");
            confirmedDate = dateCreate(atoi(confirmedDateTokens[0]), atoi(confirmedDateTokens[1]), atoi(confirmedDateTokens[2]));
        }

        // Patient released date
        PtDate releasedDate;
        if(strlen(tokens[8]) == 0) {
            releasedDate = dateCreate(0,0,0);
        } else {
            char **releasedDateTokens = split(tokens[8], 3, "/");
            releasedDate = dateCreate(atoi(releasedDateTokens[0]), atoi(releasedDateTokens[1]), atoi(releasedDateTokens[2]));
        }

        // Patient deceased date
        PtDate deceasedDate;
        if(strlen(tokens[9]) == 0) {
            deceasedDate = dateCreate(0,0,0);
        } else {
            char **deceasedDateTokens = split(tokens[9], 3, "/");
            deceasedDate = dateCreate(atoi(deceasedDateTokens[0]), atoi(deceasedDateTokens[1]), atoi(deceasedDateTokens[2]));
            datePrint(deceasedDate);
            printf("\n\n");
        }


        ListElem patient = patientCreate(atol(tokens[0]),
                                         tokens[1],
                                         atoi(tokens[2]),
                                         tokens[3],
                                         tokens[4],
                                         tokens[5],
                                         atol(tokens[6]),
                                         confirmedDate,
                                         releasedDate,
                                         deceasedDate,
                                         tokens[10]);
        
        /*Release of memory alocated in function split*/
        free(tokens);

        int error_code = listAdd(*listPatient, countPatient, patient);

        if(error_code == LIST_FULL ||
           error_code == LIST_INVALID_RANK ||
           error_code == LIST_NO_MEMORY ||
           error_code == LIST_NULL) {

            printf("An error ocurred... Please try again... \n");
            return;
        }

        countPatient++;
    }

    printf("\n\n%d patients were read!\n\n", countPatient);
    fclose(f);
}

