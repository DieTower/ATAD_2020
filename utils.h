/**
 * @file utils.h
 * @brief Useful code (module)
 * @date 2020-05-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "list.h"
#include "map.h"

/**
 * @brief This function will convert a string to lowercase
 * 
 * @param str1 [in]
 * @param str2 [out]
 */
void lowerCase(char *str1, char *str2);

/**
 * @brief This function will convert a string to uppercase
 * 
 * @param str1 [in]
 * @param str2 [out]
 */
void upperCase(char *str1, char *str2);

/**
 * @brief This function will be used to split a string in order to obtain the desired information
 * 
 * @param string 
 * @param nFields 
 * @param delim 
 * @return char** 
 */
char** split(char *string, int nFields, const char *delim);

/**
 * @brief This function will count the number of chars and compare to the given char
 * 
 * @param str 
 * @param c 
 * @return int 
 */
int strCountChar(char *str, const char *c);

/**
 * @brief This function will unite two splited strings
 * 
 * @param str 
 * @param delim 
 * @param res 
 */
void splitJoin(char *str, const char *delim, char *res);

/**
 * @brief This function will import the regions csv file
 * For that the received data will be formatted in a type that the c language can understand and do data manipulation
 * 
 * @param filename 
 * @param mapRegion 
 */
void importPatientsFromFile(char * filename, PtList *listPatient);

/**
 * @brief This function will import a given patients csv file
 * For that the received data will be formatted in a type that the c language can understand and do data manipulation
 * The data will be saved inside the given PtList
 * 
 * @param filename 
 * @param listPatient 
 */
void importRegionsFromFile(char * filename, PtMap *mapRegion);

/**
 * @brief This function will count all patients from each status and give an average of each
 * 
 * @param listPatient [in]
 * @param status [out]
 */
void patientsAVG(PtList listPatient, char *status);

/**
 * @brief This function will receive a patient's id and print the information about them.
 * 
 * @param listPatient [in]
 * @param id [out] 
 */
void patientsFOLLOW(PtList listPatient, long int id);

/**
 * @brief This function will count all the patients inside the given PtList
 * 
 * @param listPatient
 * @return int 
 */
int getCountPatients(PtList listPatient);

/**
 * @brief This function will count all patients and return a percentage of patients of each sex.
 * 
 * @param listPatient [in]
 * @param sex [out]
 */
void patientsSEX(PtList listPatient, char *sex);

/**
 * @brief This function will print the information of the given patient
 * 
 * @param listPatient 
 * @param id 
 */
void patientsSHOW(PtList listPatient, long int id);

/**
 * @brief This function will return a list with the top 5 patients that took longer to recover
 * 
 * @param listPatient 
 */
void patientsTOP5(PtList listPatient);

/**
 * @brief This function will return the oldest patient of each sex of the given list
 * 
 * @param listPatient 
 */
void patientsOLDEST(PtList listPatient);

/**
 * @brief This function will print the growth of infection between two dates
 * 
 * @param listPatient 
 * @param date 
 */
void patientsGROWTH(PtList listPatient, PtDate date);

/**
 * @brief This function will return a matrix that will show the number of patients of some certains group ages and the status
 * 
 * @param listPatient 
 */
void patientsMATRIX(PtList listPatient);

/**
 * @brief This function will return the regions with infected
 * 
 * @param listPatient 
 * @param mapRegion 
 */
void patientsREGIONS(PtList listPatient, PtMap mapRegion);

/**
 * @brief 
 * 
 * @param listPatient 
 * @param mapRegion 
 */
void patientsREPORT(PtList listPatient, PtMap mapRegion);
