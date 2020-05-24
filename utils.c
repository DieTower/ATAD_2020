/**
 * @file utils.c
 * @brief Useful code
 * @date 2020-05-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "utils.h"

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



// void importKahootReportsFromFile(char * filename, PtList *listKR) {
//     FILE *f = NULL;

//     f = fopen(filename, "r");

//     if(f == NULL) {
//         printf("An error ocurred... It was not possible to open the file %s ...\n", filename);
//         return;
//     }

//     char nextline[1024];

//     int countKR = 0; //kahoot report count
//     bool firstLine = true;

//     while(fgets(nextline, sizeof(nextline), f)) {
//         if(strlen(nextline) < 1)
//             continue;

//         /*AS the first line of the file contains the names of the fields it should be ignored*/
//         if(firstLine) {
//             firstLine = false;
//             continue;
//         }

//         char **tokens = split(nextline, 6, ";");

//         //At this moment the tokens array is composed with the following "strings"
//         //tokens[0] = week
//         //tokens[1] = rank
//         //tokens[2] = nickname
//         //tokens[3] = total_score
//         //tokens[4] = correct_answers
//         //tokens[5] = incorrect_answers

//         ListElem kr = kahootReportCreate(atoi(tokens[0]),
//                                      atoi(tokens[1]),
//                                      tokens[2],
//                                      atoi(tokens[3]),
//                                      atoi(tokens[4]),
//                                      atoi(tokens[5]));
        
//         free(tokens); // release of the memory alocated in function split

//         int error_code = listAdd(*listKR, countKR, kr);

//         if(error_code == LIST_FULL ||
//            error_code == LIST_INVALID_RANK ||
//            error_code == LIST_NO_MEMORY ||
//            error_code == LIST_NULL) {

//             printf("An error ocurred... Please try again... \n");
//             return;
//         }

//         countKR++;
//     }

    
//     printf("\n\n%d kahoot reports were read!\n\n", countKR);
//     fclose(f);
// };

