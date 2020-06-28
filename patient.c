/**
 * @file patient.c
 * @author Rodrigo Costa
 * @author Nicole Vieira
 * @brief Patient data module implementation
 * @date 2020-05-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "patient.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct patient {
    long int id;
    char sex[6]; // {"male", "female"}
    int birthYear;
    char country[40]; // birth country
    char region[40];
    char infectionReason[100];
    long int infectedBy; // id of infected patient
    PtDate confirmedDate;
    PtDate releasedDate;
    PtDate deceasedDate;
    char status[10]; // {"isolated","released","deceased"}
} Patient;

/**
 * @brief This function will create a PtPatient type by allocation memory with calloc
 * If the allocation is successful all the values will be empty
 * Finally the new PtPatient will return
 * 
 * @param id 
 * @param sex 
 * @param birthYear 
 * @param country 
 * @param region 
 * @param infectionReason 
 * @param infectedBy 
 * @param confirmedDate 
 * @param releasedDate 
 * @param deceasedDate 
 * @param status 
 * @return PtPatient 
 */
PtPatient patientCreate(
    long int id,
    char sex[6],
    int birthYear,
    char country[40],
    char region[40],
    char infectionReason[100],
    long int infectedBy,
    PtDate confirmedDate,
    PtDate releasedDate,
    PtDate deceasedDate,
    char status[10]
) {
    PtPatient patient = (PtPatient) calloc(1, sizeof(Patient));

    if(patient == NULL) return NULL;

    patient->id = id;
    // memcpy(patient->sex, sex, (sizeof(patient->sex)+1));
    strcpy(patient->sex, sex);
    patient->birthYear = birthYear;
    // memcpy(patient->country, country, (sizeof(patient->country)+1));
    strcpy(patient->country, country);
    // memcpy(patient->region, region, (sizeof(patient->region)+1));
    strcpy(patient->region, region);
    // memcpy(patient->infectionReason, infectionReason, (sizeof(patient->infectionReason)+1));
    strcpy(patient->infectionReason, infectionReason);
    patient->infectedBy = infectedBy;
    patient->confirmedDate = dateCreate(confirmedDate->day, confirmedDate->month, confirmedDate->year);
    patient->releasedDate = dateCreate(releasedDate->day, releasedDate->month, releasedDate->year);
    patient->deceasedDate = dateCreate(deceasedDate->day, deceasedDate->month, deceasedDate->year);
    // memcpy(patient->status, status, (sizeof(patient->status)+1));
    strcpy(patient->status, status);

    return patient;
}

/**
 * @brief This function will destroy a given PtPatient but first will verify if it's valid and finally the function will free the used memory.
 * 
 * @param p 
 * @return int 
 */
int patientDestroy(PtPatient *p) {

    if(*p == NULL) return PATIENT_NULL;

    PtPatient patient = *p;

    dateDestroy(&patient->confirmedDate);

    dateDestroy(&patient->releasedDate);

    dateDestroy(&patient->deceasedDate);

    free(patient);
    *p = NULL;

    return PATIENT_OK;
}

/**
 * @brief This function will print a patient with all the necessary info
 * 
 * @param p 
 */
void patientPrint(PtPatient p) {

    if(p == NULL) {

        printf("(NULL)\n");

    } else {

        printf("%ld | %-6s | %-4d | %-10s \t| %-15s \t| %-25s \t\t| %-10ld \t| ", p->id, p->sex, p->birthYear, p->country, p->region, p->infectionReason, p->infectedBy);
        printf("%02d-%02d-%-4.04d | ", p->confirmedDate->day, p->confirmedDate->month, p->confirmedDate->year);
        printf("%02d-%02d-%-4.04d | ", p->releasedDate->day, p->releasedDate->month, p->releasedDate->year);
        printf("%02d-%02d-%-4.04d | ", p->deceasedDate->day, p->deceasedDate->month, p->deceasedDate->year);
        printf("%s\n", p->status);
    }

}

/**
 * @brief This function will print a patient with a basic print type 
 * First all the values will be verified to see if there are any unknown values to implement in the print
 * 
 * @param p 
 * @param direction 
 */
void patientDirectedPrint(PtPatient p, char direction) {

    // Check if birth day exist and set the age
    int age = 0;
    patientAge(p, &age);

    char patient_age[50] = " ";
    if(age == -1) {
        strcpy(patient_age, "unknown");
    } else {
        char buffer[50] = " ";
        sprintf(buffer, "%d", age);
        strcpy(patient_age, buffer);
    }

    // Check if data about the patient sex exist and set sex
    char patient_sex[50] = " ";
    if(strlen(p->sex) == 0)  {
        strcpy(patient_sex, "unknown");
    } else {
        strcpy(patient_sex, p->sex);
    }

    if(direction == 'h') {

        printf("ID: %ld, SEX: %s, AGE: %s, COUNTRY/REGION: %s/%s, STATE: %s", p->id, patient_sex, patient_age, p->country, p->region, p->status);
    
    } else if(direction == 'v') {
        
        printf("ID: %ld\nSEX: %s\nAGE: %s\nCOUNTRY/REGION: %s/%s\nINFECTED REASON: %s\nSTATE: %s", p->id, patient_sex, patient_age, p->country, p->region, p->infectionReason, p->status);

    } else {

        printf("(NULL) \n");
    }
}

/**
 * @brief This function will give a patient's id but first will verify if the patient is valid
 * 
 * @param p 
 * @param id 
 * @return int 
 */
int patientId(PtPatient p, long int *id) {

    if(p == NULL) return PATIENT_NULL;

    (*id) = p->id;

    return PATIENT_OK;
}

/**
 * @brief This function will give a patient's sex but first will verify if the patient is valid
 * 
 * @param p 
 * @param sex 
 * @return int 
 */
int patientSex(PtPatient p, char *sex) {

    if(p == NULL) return PATIENT_NULL;

    memcpy(sex, p->sex, sizeof(p->sex));

    return PATIENT_OK;
}

/**
 * @brief This function will give a patient's birth year but first will verify if the patient is valid
 * 
 * @param p 
 * @param birthYear 
 * @return int 
 */
int patientBithYear(PtPatient p, int *birthYear) {

    if(p == NULL) return PATIENT_NULL;

    (*birthYear) = p->birthYear;

    return PATIENT_OK;
}

/**
 * @brief This function will give a patient's country but first will verify if the patient is valid
 * 
 * @param p 
 * @param country 
 * @return int 
 */
int patientCountry(PtPatient p, char *country) {

    if(p == NULL) return PATIENT_NULL;

    memcpy(country, p->country, sizeof(p->country));

    return PATIENT_OK;
}

/**
 * @brief This function will give a patient's region but first will verify if the patient is valid
 * 
 * @param p 
 * @param region 
 * @return int 
 */
int patientRegion(PtPatient p, char *region) {

    if(p == NULL) return PATIENT_NULL;

    memcpy(region, p->region, sizeof(p->region));

    return PATIENT_OK;
}

/**
 * @brief This function will give a patient's infection reason but first will verify if the patient is valid
 * 
 * @param p 
 * @param infectionReason 
 * @return int 
 */
int patientInfectionReason(PtPatient p, char *infectionReason) {

    if(p == NULL) return PATIENT_NULL;

    memcpy(infectionReason, p->infectionReason, sizeof(p->infectionReason));

    return PATIENT_OK;
}

/**
 * @brief This function will give a patient's infection cause but first will verify if the patient is valid
 * 
 * @param p 
 * @param infectedBy 
 * @return int 
 */
int patientInfectedBy(PtPatient p, long int *infectedBy) {

    if(p == NULL) return PATIENT_NULL;

    (*infectedBy) = p->infectedBy;

    return PATIENT_OK;
}

/**
 * @brief This function will give a patient's infection confirmed date but first will verify if the patient is valid
 * 
 * @param p 
 * @param confirmedDate 
 * @return int 
 */
int patientConfirmedDate(PtPatient p, PtDate *confirmedDate) {

    if(p == NULL) return PATIENT_NULL;

    (*confirmedDate) = p->confirmedDate;

    return PATIENT_OK;
}

/**
 * @brief This function will give a patient's released date but first will verify if the patient is valid
 * 
 * @param p 
 * @param releasedDate 
 * @return int 
 */
int patientReleasedDate(PtPatient p, PtDate *releasedDate) {

    if(p == NULL) return PATIENT_NULL;

    (*releasedDate) = p->releasedDate;

    return PATIENT_OK;
}

/**
 * @brief This function will give a patient's deceased date but first will verify if the patient is valid
 * 
 * @param p 
 * @param deceasedDate 
 * @return int 
 */
int patientDeceasedDate(PtPatient p, PtDate *deceasedDate) {

    if(p == NULL) return PATIENT_NULL;

    (*deceasedDate) = p->deceasedDate;

    return PATIENT_OK;
}

/**
 * @brief This function will give a patient's status but first will verify if the patient is valid
 * 
 * @param p 
 * @param status 
 * @return int 
 */
int patientStatus(PtPatient p, char *status) {

    if(p == NULL) return PATIENT_NULL;

    strcpy(status, p->status);

    return PATIENT_OK;
}

/**
 * @brief This function will give a patient's age but first will verify if the patient is valid
 * 
 * @param p 
 * @param age 
 * @return int 
 */
int patientAge(PtPatient p, int *age) {

    if(p == NULL) return PATIENT_NULL;

    int birthYear = 0;
    int error_code = patientBithYear(p, &birthYear);

    if(error_code != 0) return PATIENT_NULL;

    if(birthYear == -1) {
        *age = birthYear;
    } else {
        *age = 2020 - birthYear;
    }

    return PATIENT_OK;
}