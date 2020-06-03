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
 * @brief Create a patient
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
 * @brief Destroy a patient
 * 
 * @param p 
 * @return int 
 */
int patientDestroy(PtPatient *p);

/**
 * @brief Print a patient
 * 
 * @param p 
 */
void patientPrint(PtPatient p);

/**
 * @brief Basic print from patient 
 * 
 * @param p 
 * @param direction [h(horizontal) | v(vertical)]
 */
void patientDirectedPrint(PtPatient p, char direction);

/**
 * @brief Return a id from patient
 * 
 * @param p [in]
 * @param id [out]
 * @return int 
 */
int patientId(PtPatient p, long int *id);

/**
 * @brief Return a sex from patient
 * 
 * @param p [in]
 * @param sex [out]
 * @return int 
 */
int patientSex(PtPatient p, char *sex);

/**
 * @brief Return a birthYear from patient
 * 
 * @param p [in]
 * @param birthYear [out]
 * @return int 
 */
int patientBithYear(PtPatient p, int *birthYear);

/**
 * @brief Return a country from patient
 * 
 * @param p [in]
 * @param country [out]
 * @return int 
 */
int patientCountry(PtPatient p, char *country);

/**
 * @brief Return a region from patient
 * 
 * @param p [in]
 * @param region [out]
 * @return int 
 */
int patientRegion(PtPatient p, char *region);

/**
 * @brief Return a infectionReason from patient
 * 
 * @param p [in]
 * @param infectionReason [out]
 * @return int 
 */
int patientInfectionReason(PtPatient p, char *infectionReason);

/**
 * @brief Return a infectedBy from patient
 * 
 * @param p 
 * @param infectedBy 
 * @return int 
 */
int patientInfectedBy(PtPatient p, long int *infectedBy);

/**
 * @brief Return a confirmedDate from patient
 * 
 * @param p [in]
 * @param confirmedDate [out]
 * @return int 
 */
int patientConfirmedDate(PtPatient p, PtDate *confirmedDate);

/**
 * @brief Return a releasedDate patient
 * 
 * @param p [in]
 * @param releasedDate [out]
 * @return int 
 */
int patientReleasedDate(PtPatient p, PtDate *releasedDate);

/**
 * @brief Return a deceasedDate from patient
 * 
 * @param p [in]
 * @param deceasedDate [out]
 * @return int 
 */
int patientDeceasedDate(PtPatient p, PtDate *deceasedDate);

/**
 * @brief Return a status from patient
 * 
 * @param p [in]
 * @param status [out]
 * @return int 
 */
int patientStatus(PtPatient p, char *status);

/**
 * @brief Return a Age of one patient
 * 
 * @param p [in]
 * @param age [out]
 * @return int 
 */
int patientAge(PtPatient p, int *age);