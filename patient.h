/**
 * @file patient.h
 * @author Rodrigo Costa
 * @author Nicole Vieira
 * @brief Patient data module
 * @date 2020-05-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#define PATIENT_OK 0
#define PATIENT_NULL 1

#include "date.h"

struct patient;
typedef struct patient* PtPatient;

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
);

/**
 * @brief This function will destroy a given PtPatient but first will verify if it's valid and finally the function will free the used memory.
 * 
 * @param p 
 * @return int 
 */
int patientDestroy(PtPatient *p);

/**
 * @brief This function will print a patient with all the necessary info
 * 
 * @param p 
 */
void patientPrint(PtPatient p);

/**
 * @brief This function will print a patient with a basic print type 
 * First all the values will be verified to see if there are any unknown values to implement in the print
 * 
 * @param p 
 * @param direction 
 */
void patientDirectedPrint(PtPatient p, char direction);

/**
 * @brief This function will give a patient's id but first will verify if the patient is valid
 * 
 * @param p [in]
 * @param id [out]
 * @return int 
 */
int patientId(PtPatient p, long int *id);

/**
 * @brief This function will give a patient's sex but first will verify if the patient is valid
 * 
 * @param p [in]
 * @param sex [out]
 * @return int 
 */
int patientSex(PtPatient p, char *sex);

/**
 * @brief This function will give a patient's birth year but first will verify if the patient is valid
 * 
 * @param p [in]
 * @param birthYear [out]
 * @return int 
 */
int patientBithYear(PtPatient p, int *birthYear);

/**
 * @brief This function will give a patient's country but first will verify if the patient is valid
 * 
 * @param p [in]
 * @param country [out]
 * @return int 
 */
int patientCountry(PtPatient p, char *country);

/**
 * @brief This function will give a patient's region but first will verify if the patient is valid
 * 
 * @param p [in]
 * @param region [out]
 * @return int 
 */
int patientRegion(PtPatient p, char *region);

/**
 * @brief This function will give a patient's infection reason but first will verify if the patient is valid
 * 
 * @param p [in]
 * @param infectionReason [out]
 * @return int 
 */
int patientInfectionReason(PtPatient p, char *infectionReason);

/**
 * @brief This function will give a patient's infection cause but first will verify if the patient is valid
 * 
 * @param p [in]
 * @param infectedBy [out]
 * @return int 
 */
int patientInfectedBy(PtPatient p, long int *infectedBy);

/**
 * @brief This function will give a patient's infection confirmed date but first will verify if the patient is valid
 * 
 * @param p [in]
 * @param confirmedDate [out]
 * @return int 
 */
int patientConfirmedDate(PtPatient p, PtDate *confirmedDate);

/**
 * @brief This function will give a patient's released date but first will verify if the patient is valid
 * 
 * @param p [in]
 * @param releasedDate [out]
 * @return int 
 */
int patientReleasedDate(PtPatient p, PtDate *releasedDate);

/**
 * @brief This function will give a patient's deceased date but first will verify if the patient is valid
 * 
 * @param p [in]
 * @param deceasedDate [out]
 * @return int 
 */
int patientDeceasedDate(PtPatient p, PtDate *deceasedDate);

/**
 * @brief This function will give a patient's status but first will verify if the patient is valid
 * 
 * @param p [in]
 * @param status [out]
 * @return int 
 */
int patientStatus(PtPatient p, char *status);

/**
 * @brief This function will give a patient's age but first will verify if the patient is valid
 * 
 * @param p [in]
 * @param age [out]
 * @return int 
 */
int patientAge(PtPatient p, int *age);