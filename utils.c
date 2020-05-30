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
#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void lowerCase(char *str1, char *str2) {
    int size = (int)strlen(str1);
    
    for(int i = 0; i < size; i++) {
        str2[i] = tolower(str1[i]);
    }

    str2[size] = '\0';
};

void upperCase(char *str1, char *str2) {
    int size = (int)strlen(str1);
    
    for(int i = 0; i < size; i++) {
        str2[i] = toupper(str1[i]);
    }

    str2[size] = '\0';
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

int strCountChar(char *str, const char *c) {

    int count = 0;

    for(int i=0; i<strlen(str); i++) {
        if(str[i] == c[0]) {
            count++;
        }
    }

    return count;
}

void splitJoin(char *str, const char *delim, char *res) {
    
    int nFields =  strCountChar(str, delim);

    char field[nFields];
    strcpy(field, str);

    char **tokens = split(field, (nFields+1), delim);

    for(int i=0; i<(nFields+1); i++) {
        strcat(res, tokens[i]);
    }

    free(tokens);
}

MapKey keyCreate(char str[100]) {
    MapKey key = (MapKey) calloc(1, sizeof(char[100]));

    if(key == NULL) return NULL;

    strcpy(key, str);

    return key;
}

int keyDestroy(MapKey *c) {
    
    MapKey key = *c;

    if(key == NULL) return REGION_NULL;

    free(key);
    *c = NULL;

    return REGION_OK;
}

void importRegionsFromFile(char * filename, PtMap *mapRegion) {
    FILE *f = NULL;

    f = fopen(filename, "r");

    if(f == NULL) {
        // printf("An error ocurred... It wad not possible to open the file %s ...\n", filename);
        printf("File not found");
        return;
    }

    char nextline[1024];

    int countRegion = 0; // region count
    bool firstLine = true;

    while(fgets(nextline, sizeof(nextline), f)) {

        if(strlen(nextline) < 1)
            continue;

        /* --- As the first lin ef the file contains the names of the fields it should be ignored--- */
        if(firstLine) {
            firstLine = false;
            continue;
        }

        char **tokens = split(nextline, 4, ";");
        
        /* --- At this moment the tokens array is composed with the following "strings" --- */
        // tokens[0] = regions
        // tokens[1] = city
        // tokens[2] = area
        // tokens[3] = populpation
        
        MapKey key = keyCreate(tokens[0]);
        
        // Population
        char population[100] = " ";
        splitJoin(tokens[2], ",", population);

        // Area
        char area[100] = " ";
        splitJoin(tokens[3], ",", area);

        MapValue value = regionCreate(tokens[0],
                                      tokens[1],
                                      atoi(population),
                                      atof(area));

        /* --- Release of memory alocated in function split --- */
        free(tokens);

        int error_code = mapPut(*mapRegion, key, value);

        if(error_code == MAP_FULL ||
           error_code == MAP_UNKNOWN_KEY ||
           error_code == MAP_NO_MEMORY ||
           error_code == MAP_NULL) {

            printf("An error ocurred... Please try again... \n");
            return;
        }

        countRegion++;
    }

    printf("\n\n%d regions were read!\n\n", countRegion);
    fclose(f);

}

void importPatientsFromFile(char * filename, PtList *listPatient) {
    FILE *f = NULL;

    f = fopen(filename, "r");

    if(f == NULL) {
        // printf("An error ocurred... It wad not possible to open the file %s ...\n", filename);
        printf("File not found");
        return;
    }

    char nextline[1024];

    int countPatient = 0; // patient count
    bool firstLine = true;

    while(fgets(nextline, sizeof(nextline), f)) {
        if(strlen(nextline) < 1)
            continue;

        /* --- As the first line of the file contains the names of the fields it should be ignored --- */
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

        /* --- Set data from patient --- */

        // If birth_day is null the data needs be -1
        int birth_year = atoi(tokens[2]);
        if(birth_year == 0) {
            birth_year = -1;
        }

        // If infected_by is null the data needs be -1
        long int infected_by = atol(tokens[6]);
        if(infected_by == 0) {
            infected_by = -1;
        }

        // Patient confirmed date
        PtDate confirmedDate;
        char **confirmedDateTokens;
        if(strlen(tokens[7]) == 0) {
            confirmedDate = dateCreate(0,0,0);
        } else {
            confirmedDateTokens = split(tokens[7], 3, "/");
            confirmedDate = dateCreate(atoi(confirmedDateTokens[0]), atoi(confirmedDateTokens[1]), atoi(confirmedDateTokens[2]));
        }

        // // Patient released date
        PtDate releasedDate;
        char **releasedDateTokens;
        //printf("Token: %s\n", tokens[8]);
        //printf("Length: %ld\n\n", strlen(tokens[8]));
        if(strlen(tokens[8]) == 0) {
            releasedDate = dateCreate(0,0,0);
        } else {
            releasedDateTokens = split(tokens[8], 3, "/");
            releasedDate = dateCreate(atoi(releasedDateTokens[0]), atoi(releasedDateTokens[1]), atoi(releasedDateTokens[2]));
        }

        // // Patient deceased date
        PtDate deceasedDate;
        char **deceasedDateTokens;
        if(strlen(tokens[9]) == 0) {
            deceasedDate = dateCreate(0,0,0);
        } else {
            deceasedDateTokens = split(tokens[9], 3, "/");
            deceasedDate = dateCreate(atoi(deceasedDateTokens[0]), atoi(deceasedDateTokens[1]), atoi(deceasedDateTokens[2]));
        }

        ListElem patient = patientCreate(atol(tokens[0]),
                                         tokens[1],
                                         birth_year,
                                         tokens[3],
                                         tokens[4],
                                         tokens[5],
                                         infected_by,
                                         confirmedDate,
                                         releasedDate,
                                         deceasedDate,
                                         tokens[10]);
        
        if(strlen(tokens[7]) != 0) free(confirmedDateTokens);
        if(strlen(tokens[8]) != 0) free(releasedDateTokens);
        if(strlen(tokens[9]) != 0) free(deceasedDateTokens);

        free(confirmedDate);
        free(releasedDate);
        free(deceasedDate);

        /* --- Release of memory alocated in function split --- */
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

