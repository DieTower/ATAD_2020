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

int patientDestroy(PtPatient *p) {

    PtPatient patient = *p;

    if(patient == NULL) return PATIENT_NULL;

    dateDestroy(&patient->confirmedDate);

    dateDestroy(&patient->releasedDate);

    dateDestroy(&patient->deceasedDate);

    free(patient);
    *p = NULL;

    return PATIENT_OK;
}

void patientPrint(PtPatient p) {

    if(p == NULL) {

        printf("(NULL)\n");

    } else {

        printf("%-4ld | %-6s | %-4d | %-10s \t| %-15s \t| %-25s \t\t| %-10ld \t| ", p->id, p->sex, p->birthYear, p->country, p->region, p->infectionReason, p->infectedBy);
        printf("%02d-%02d-%-4.04d | ", p->confirmedDate->day, p->confirmedDate->month, p->confirmedDate->year);
        printf("%02d-%02d-%-4.04d | ", p->releasedDate->day, p->releasedDate->month, p->releasedDate->year);
        printf("%02d-%02d-%-4.04d | ", p->deceasedDate->day, p->deceasedDate->month, p->deceasedDate->year);
        printf("%s\n", p->status);
    }

}

int patientId(PtPatient p, long int *id) {

    if(p == NULL) return PATIENT_NULL;

    (*id) = p->id;

    return PATIENT_OK;
}

int patientSex(PtPatient p, char *sex) {

    if(p == NULL) return PATIENT_NULL;

    memcpy(sex, p->sex, sizeof(p->sex));

    return PATIENT_OK;
}

int patientBithYear(PtPatient p, int *birthYear) {

    if(p == NULL) return PATIENT_NULL;

    (*birthYear) = p->birthYear;

    return PATIENT_OK;
}

int patientCountry(PtPatient p, char *country) {

    if(p == NULL) return PATIENT_NULL;

    memcpy(country, p->country, sizeof(p->country));

    return PATIENT_OK;
}

int patientRegion(PtPatient p, char *region) {

    if(p == NULL) return PATIENT_NULL;

    memcpy(region, p->region, sizeof(p->region));

    return PATIENT_OK;
}

int patientInfectionReason(PtPatient p, char *infectionReason) {

    if(p == NULL) return PATIENT_NULL;

    memcpy(infectionReason, p->infectionReason, sizeof(p->infectionReason));

    return PATIENT_OK;
}

int patientConfirmedDate(PtPatient p, PtDate *confirmedDate) {

    if(p == NULL) return PATIENT_NULL;

    (*confirmedDate) = p->confirmedDate;

    return PATIENT_OK;
}

int patientReleasedDate(PtPatient p, PtDate *releasedDate) {

    if(p == NULL) return PATIENT_NULL;

    (*releasedDate) = p->releasedDate;

    return PATIENT_OK;
}

int patientDeceasedDate(PtPatient p, PtDate *deceasedDate) {

    if(p == NULL) return PATIENT_NULL;

    (*deceasedDate) = p->deceasedDate;

    return PATIENT_OK;
}

int patientStatus(PtPatient p, char *status) {

    if(p == NULL) return PATIENT_NULL;

    memcpy(status, p->status, sizeof(p->status));

    return PATIENT_OK;
}