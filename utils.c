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

/**
 * @brief This function will import the regions csv file
 * For that the received data will be formatted in a type that the c language can understand and do data manipulation
 * 
 * @param filename 
 * @param mapRegion 
 */
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
        
        MapKey key = stringCodeCreate(tokens[0]);
        
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

/**
 * @brief This function will import a given patients csv file
 * For that the received data will be formatted in a type that the c language can understand and do data manipulation
 * The data will be saved inside the given PtList
 * 
 * @param filename 
 * @param listPatient 
 */
void importPatientsFromFile(char * filename, PtList *listPatient) {
    FILE *f = NULL;

    f = fopen(filename, "r");

    if(f == NULL) {
        // printf("An error ocurred... It wad not possible to open the file %s ...\n", filename);
        printf("File not found\n");
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

int regionFromPatient(PtMap m, PtPatient p, PtRegion *r) {

    if(p == NULL) return PATIENT_NULL;

    char k[50] = " ";
    patientRegion(p, k);
    MapKey key = stringCodeCreate(k);

    PtRegion region = *r;
    mapGet(m, key, &region);
    
    return PATIENT_OK;
}

void maxDateInFile(PtList listPatient, PtDate *date) {

    int size = 0;
    listSize(listPatient, &size);

    ListElem patient;
    PtDate patient_date;
    
    PtDate date_max;

    listGet(listPatient, 0, &patient);
    patientConfirmedDate(patient, &date_max);

    for(int i=1; i<=size; i++) {

        // Patient
        listGet(listPatient, i, &patient);
        patientConfirmedDate(patient, &patient_date);
        
        biggestDate(date_max, patient_date, &date_max);
        
    }

    *date = date_max;
}

// ----- COMMAND Functions -----

void patientsAVG(PtList listPatient, char *status) {
    
    int sum = 0;
    int count = 0;

    int size = 0;
    listSize(listPatient, &size);

    ListElem patient;
    char statusFromPatient[50] = " ";

    for(int i=0; i<=size; i++) {
        
        listGet(listPatient, i, &patient);
        patientStatus(patient, statusFromPatient);

        int birthYear;
        int error_code = patientBithYear(patient, &birthYear);
        
        if(strncmp(statusFromPatient, status, sizeof(status)) == 0 && error_code == 0 && birthYear != -1) {
            int age = 2020 - birthYear;
            sum += age;
            count++;
        }
    }

    int avg = sum/count;

    printf("Average Age for %s patients: %d\n", status, avg);
}

void patientsFOLLOW(PtList listPatient, long int id) {

    int size = 0;
    listSize(listPatient, &size);

    ListElem patient;
    long int infectedBy = 0;
    
    long int patient_id = id;

    long int currentID = 0;
    int firstPatient = false;

    // Run until don't exist more infectedBy chain
    while(patient_id != -1) {
        
        int error_code = 0;

        // Run all the patients
        for(int i=0; i<=size; i++) {
            
            // Get the patient by rank
            int error_code = listGet(listPatient, i, &patient);
            
            // Check if listGet found the patient
            if(error_code != 0) break;
            
            // Insert the id in currentID
            patientId(patient, &currentID);

            // If current id is the the same of the patient in chain 
            if(currentID == patient_id) {
                
                // Print
                if(firstPatient) {
                    printf("contaminated by Patient: ");
                } else {
                    printf("Following Patient: ");
                }

                patientDirectedPrint(patient, 'h');

                // Set the infectedBy as id
                patientInfectedBy(patient, &infectedBy);
                patient_id = infectedBy;

                // Check if exist a infectedBy, if not print that
                if(!firstPatient && patient_id == -1) {
                    printf("contaminated by: unknown\n");
                }

                firstPatient = true;
            }

        }

        if(error_code != 0) break;
    }
}

int getCountPatients(PtList listPatient){
    int size = 0;
    listSize(listPatient, &size);

    return size;
}

void patientsSEX(PtList listPatient, char *sex) {

    int size = 0;
    listSize(listPatient, &size);

    ListElem patient;
    char sexFromPatient[50] = " ";

    int count = 0;
    for(int i=0; i<=size; i++) {

        listGet(listPatient, i, &patient);
        patientSex(patient, sexFromPatient);


            if(strncmp(sexFromPatient, sex, sizeof(sex)) == 0 && strncmp("unknown", sex, sizeof(sex)) != 0) {
                count++;
            } else if(strncmp("", sexFromPatient, sizeof(sexFromPatient)) == 0) {
                count++;
            }
    }

    double percentage = (double)(count*100)/size;
    printf("Percentage of %s: %.2f%%\n", sex, percentage);
}

void patientsSHOW(PtList listPatient, long int id) {

    int size = 0;
    listSize(listPatient, &size);

    PtDate date1;
    PtDate date2;

    char status[20] = " ";

    ListElem patient;
    long int patient_id = 0;

    for(int i=0; i<=size; i++) {

        listGet(listPatient, i, &patient);
        patientId(patient, &patient_id);

        if(patient_id == id) {
            patientDirectedPrint(patient, 'v');

            patientConfirmedDate(patient, &date1);

            char status[20] = " ";
            patientStatus(patient, status);

            if(strncmp(status, "isolated", 8) == 0) {

                maxDateInFile(listPatient, &date2);

            } else if(strncmp(status, "released", 8) == 0) {

                patientReleasedDate(patient, &date2);

            } else if(strncmp(status, "deceased", 8) == 0) {
                
                patientDeceasedDate(patient, &date2);
                
            }
        }
    }

    int day = 0;
    int error_code = diffDates(date1, date2, &day);

    char buffer[50] = " ";
    if(error_code == 0) {
        sprintf(buffer, "%d", day);
    } else {
        strcpy(buffer, "unknown");
    }

    printf("NUMBER OF DAYS WITH ILLNESS: %s\n", buffer);
}

void patientsTOP5(PtList listPatient){
    
    int size = 0;
    listSize(listPatient, &size);

    ListElem patient;
    ListElem patients[size];
    ListElem a;

    PtDate date1, date2, date3, date4;

    int day = 0;
    int day2 = 0;
    int age, age2;

    for(int k = 0; k < size; k++){
        listGet(listPatient, k, &patient);

        patients[k] = patient;
    }

    for (int i = 0; i < size; ++i) 
    {
        for (int j = i + 1; j < size; ++j) 
        {
            patientConfirmedDate(patients[i], &date1);
            patientReleasedDate(patients[i], &date2);

            diffDates(date1, date2, &day);

            patientConfirmedDate(patients[j], &date3);
            patientReleasedDate(patients[j], &date4);

            diffDates(date3, date4, &day2);

            if (day < day2) 
            {
                a = patients[i];
                patients[i] = patients[j];
                patients[j] = a;
            }
            else if(day == day2){
                patientAge(patients[i], &age);
                patientAge(patients[j], &age2);

                if(age < age2){
                    a = patients[i];
                    patients[i] = patients[j];
                    patients[j] = a;
                }
            }
        }
    }

    long int patient_id = 0;

    for(int l = 0; l < 5; l++){
        patientId(patients[l], &patient_id);
        patientsSHOW(listPatient, patient_id);
        printf("\n");
    }
}

void patientsOLDEST(PtList listPatient){

    int size = 0;
    listSize(listPatient, &size);

    ListElem patients[size];
    ListElem patient;

    for(int i = 0; i < size; i++){
        listGet(listPatient, i, &patient);

        patients[i] = patient;
    }

    char sex[20] = " ";
    int yearMale, yearFemale;
    long int maxYearMale = 9999;
    long int maxYearFemale = 9999;

    for(int j = 0; j < size; j++){
        patientSex(patients[j], sex);

        if(strncmp(sex, "male", 8) == 0){
            patientBithYear(patients[j], &yearMale);

            if((yearMale < maxYearMale) && (yearMale != -1))
                maxYearMale = yearMale;
        }

        if(strncmp(sex, "female", 8) == 0){
            patientBithYear(patients[j], &yearFemale);

            if((yearFemale < maxYearFemale) && (yearFemale != -1))
                maxYearFemale = yearFemale;
        }
    }

    int numF = 1;
    printf("FEMALES:\n");
    for(int k = 0; k < size; k++){
        patientBithYear(patients[k], &yearFemale);
        patientSex(patients[k], sex);

        if(strncmp(sex, "female", 8) == 0){
            if(yearFemale == maxYearFemale)
            {
                printf("%d - ", numF);
                patientDirectedPrint(patients[k], 'h');
                numF++;
            }
        }
    }

    int numM = 1;
    printf("MALES:\n");
    for(int l = 0; l < size; l++){
        patientBithYear(patients[l], &yearMale);
        patientSex(patients[l], sex);

        if(strncmp(sex, "male", 8) == 0){
            if(yearMale == maxYearMale)
            {
                printf("%d - ", numM);
                patientDirectedPrint(patients[l], 'h');
                numM++;
            }
        }
    }
    
}

PtDate getDayBefore(PtDate date){

    int dateDayBefore = 0, dateMonthBefore = 0, dateYearBefore = 0;

    if(date->day-1 < 1){
        if(date->month-1 < 1){
            dateDayBefore = 31;
            dateMonthBefore = 12;
            dateYearBefore = date->year-1;
        }
        else if(date->month-1 == 1 || date->month-1 == 3 || date->month-1 == 5 || date->month-1 == 7 || date->month-1 == 8 || date->month-1 == 10){
            dateDayBefore = 31;
            dateMonthBefore = date->month-1;
            dateYearBefore = date->year;
        }
        else if(date->month-1 == 4 || date->month-1 == 6 || date->month-1 == 9 || date->month-1 == 11){
            dateDayBefore = 30;
            dateMonthBefore = date->month-1;
            dateYearBefore = date->year;
        }
        else if(date->month-1 == 2){
            dateDayBefore = 29;
            dateMonthBefore = date->month-1;
            dateYearBefore = date->year;
        }
    }
    else{
        dateDayBefore = date->day-1;
        dateMonthBefore = date->month;
        dateYearBefore = date->year;
    }

    PtDate dayBefore = dateCreate(dateDayBefore, dateMonthBefore, dateYearBefore);

    return dayBefore;
}

void patientsGROWTH(PtList listPatient, PtDate date){

    int size = 0;
    listSize(listPatient, &size);

    ListElem patients[size];
    ListElem patient;

    for(int i = 0; i < size; i++){
        listGet(listPatient, i, &patient);

        patients[i] = patient;
    }

    PtDate dayBefore = getDayBefore(date);
    PtDate confirmedDate;
    
    int numDeadBefore = 0;
    int numDeadDay = 0;
    int numIsolatedBefore = 0;
    int numIsolatedDay = 0;
    char status[20] = " ";

    PtDate datesArray[size];

    for(int j = 0; j < size; j++){
        patientConfirmedDate(patients[j], &confirmedDate);
        datesArray[j] = confirmedDate;

        patientStatus(patients[j], status);
        
        if((confirmedDate->year == date->year) && (confirmedDate->month == date->month) && (confirmedDate->day == date->day))
        {
            if(strncmp(status, "isolated", 8) == 0)
                numIsolatedDay++;

            if(strncmp(status, "deceased", 8) == 0)
                numDeadDay++;
        }

        if((confirmedDate->year == dayBefore->year) && (confirmedDate->month == dayBefore->month) && (confirmedDate->day == dayBefore->day)){
            if(strncmp(status, "isolated", 8) == 0)
                numIsolatedBefore++;

            if(strncmp(status, "deceased", 8) == 0)
                numDeadBefore++;
        }
    }

    float rateNewInfected = (((float)numIsolatedDay-(float)numIsolatedBefore)/(float)numIsolatedBefore);
    float rateNewDead = (((float)numDeadDay-(float)numDeadBefore)/(float)numDeadBefore);

    int count = 0;

    for(int k = 0; k < sizeof(datesArray) / sizeof(datesArray[0]); k++){
        if((datesArray[k]->year == date->year) && (datesArray[k]->month == date->month) && (datesArray[k]->day == date->day))
            count++;
    }

    if(count == 0)
    {
        printf("There is no record for day ");
        datePrint(date);
    }
    else{
        printf("Date: ");
        datePrint(dayBefore);
        printf("Number of dead: %d\n", numDeadBefore);
        printf("Number of isolated: %d\n", numIsolatedBefore);

        printf("\nDate: ");
        datePrint(date);
        printf("Number of dead: %d\n", numDeadDay);
        printf("Number of isolated: %d\n", numIsolatedDay);

        printf("\n");
        printf("Rate of new infected: %.2lf%%\n", rateNewInfected);
        printf("Rate of new dead: %.2lf%%\n", rateNewDead);
    }
}

void patientsMATRIX(PtList listPatient){
    
    int size = 0;
    listSize(listPatient, &size);

    ListElem patients[size];
    ListElem patient;

    for(int i = 0; i < size; i++){
        listGet(listPatient, i, &patient);

        patients[i] = patient;
    }

    int age = 0;
    char status[20] = " ";
    int countIsolated15 = 0, countDeceased15 = 0, countReleased15 = 0;
    int countIsolated30 = 0, countDeceased30 = 0, countReleased30 = 0;
    int countIsolated45 = 0, countDeceased45 = 0, countReleased45 = 0;
    int countIsolated60 = 0, countDeceased60 = 0, countReleased60 = 0;
    int countIsolated75 = 0, countDeceased75 = 0, countReleased75 = 0;
    int countIsolatedMax = 0, countDeceasedMax = 0, countReleasedMax = 0;

    for(int i = 0; i < size; i++){
        patientAge(patients[i], &age);
        patientStatus(patients[i], status);

        if(strncmp(status, "isolated", 8) == 0) {
            if(age >= 0 && age <= 15)
                countIsolated15++;
            else if (age >= 16 && age <= 30)
                countIsolated30++;
            else if (age >= 31 && age <= 45)
                countIsolated45++;
            else if (age >= 46 && age <= 60)
                countIsolated60++;
            else if (age >= 61 && age <= 75)
                countIsolated75++;
            else if (age >= 76)
                countIsolatedMax++;

        } else if(strncmp(status, "released", 8) == 0) {
            if(age >= 0 && age <= 15)
                countReleased15++;
            else if (age >= 16 && age <= 30)
                countReleased30++;
            else if (age >= 31 && age <= 45)
                countReleased45++;
            else if (age >= 46 && age <= 60)
                countReleased60++;
            else if (age >= 61 && age <= 75)
                countReleased75++;
            else if (age >= 76)
                countReleasedMax++;

        } else if(strncmp(status, "deceased", 8) == 0) {
            if(age >= 0 && age <= 15)
                countDeceased15++;
            else if (age >= 16 && age <= 30)
                countDeceased30++;
            else if (age >= 31 && age <= 45)
                countDeceased45++;
            else if (age >= 46 && age <= 60)
                countDeceased60++;
            else if (age >= 61 && age <= 75)
                countDeceased75++;
            else if (age >= 76)
                countDeceasedMax++;
        }

    }

    int disp[6][3];

    disp[0][0] = countIsolated15;
    disp[0][1] = countDeceased15;
    disp[0][2] = countReleased15;

    disp[1][0] = countIsolated30;
    disp[1][1] = countDeceased30;
    disp[1][2] = countReleased30;

    disp[2][0] = countIsolated45;
    disp[2][1] = countDeceased45;
    disp[2][2] = countReleased45;

    disp[3][0] = countIsolated60;
    disp[3][1] = countDeceased60;
    disp[3][2] = countReleased60;

    disp[4][0] = countIsolated75;
    disp[4][1] = countDeceased75;
    disp[4][2] = countReleased75;

    disp[5][0] = countIsolatedMax;
    disp[5][1] = countDeceasedMax;
    disp[5][2] = countReleasedMax;

    printf("\t\tIsolated\t\tDeceased\t\tReleased\n");

    int countLine = 0;
    for(int i = 0; i < 6; i++){
        if(countLine == 0)
            printf("[0-15]");
        if(countLine == 1)
            printf("[16-30]");
        if(countLine == 2)
            printf("[31-45]");
        if(countLine == 3)
            printf("[46-60]");
        if(countLine == 4)
            printf("[61-75]");
        if(countLine == 5)
            printf("[76...]");
        for(int j = 0; j < 3; j++){
            printf("\t\t%d\t", disp[i][j]);
            
        }
        countLine+=1;
        printf("\n");
    }
}

void patientsREGIONS(PtList listPatient, PtMap mapRegion){

    int size = 0;
    listSize(listPatient, &size);

    ListElem patient;

    int regionsSize = size;

    char **keys = (char**) malloc(sizeof(char*) * regionsSize);
    char strRegion[50] = " ";
    char status[20] = " ";
    int count = 0;

    for(int i = 0; i < size; i++){
        listGet(listPatient, i, &patient);
        patientRegion(patient, strRegion);
        patientStatus(patient, status);

        if(strncmp(status, "isolated", 8) == 0) {
            keys[count] = (char*) malloc(sizeof(char) * 250);
            strcpy(keys[count], strRegion);
            count++;
        }
    }

    MapKey temp;
    for (int i = 0; i < count; i++){
        for (int j = 0; j < count-1; j++){
            if(strcmp(keys[j], keys[j+1]) > 0){
                strcpy(temp.code, keys[j]);
                strcpy(keys[j], keys[j+1]);
                strcpy(keys[j+1], temp.code);
            }
        }
    }

    for(int i = 0; i< count; i++){
        for(int j = i+1; j< count; j++){
            if(strcmp(keys[i], keys[j]) == 0){
                for(int k = j; k < count; k++){
                    keys[k] = keys[k+1];
                }
                count--;
                j--;
            }
        }
    }

    for(int i = 0; i < count; i++){
        printf("%s\n", keys[i]);
    }

    for(int i = 0; i < count; i++){
        free(keys[i]);
    }
    
    free(keys);
}