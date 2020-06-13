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
 * @brief Put every char in one char array in lowercase
 * 
 * @param str1[in]
 * @param str2[out]
 */
void lowerCase(char *str1, char *str2);

/**
 * @brief Put every char in one char array in uppercase
 * 
 * @param str1[in]
 * @param str2[out]
 */
void upperCase(char *str1, char *str2);

/**
 * @brief Split a "string"(char array)
 * 
 * @param string 
 * @param nFields 
 * @param delim 
 * @return char** 
 */
char** split(char *string, int nFields, const char *delim);

/**
 * @brief Count how many caracters in one "string" are equal to the char inserted
 * 
 * @param str 
 * @param c 
 * @return int 
 */
int strCountChar(char *str, const char *c);

/**
 * @brief Split one "string" and join the values splited in a new one
 * 
 * @param str 
 * @param delim 
 */
void splitJoin(char *str, const char *delim, char *res);

/**
 * @brief Create a Mapkey allocation
 * 
 * @param str 
 * @return MapKey 
 */
MapKey keyCreate(char str[100]);

/**
 * @brief Destroy a Mapkey allocated
 * 
 * @param c 
 * @return int 
 */
int keyDestroy(MapKey *c);

/**
 * @brief Populate a patient list 
 * 
 * @param filename 
 * @param listPatient 
 */
void importPatientsFromFile(char * filename, PtList *listPatient);

/**
 * @brief Populate a region map
 * 
 * @param filename 
 * @param mapRegion 
 */
void importRegionsFromFile(char * filename, PtMap *mapRegion);

/**
 * @brief Finds the number of patients infected imported
 * 
 * @param listPatient [in]
 * @param status [in]
 */
void patientsAVG(PtList listPatient, char *status);

/**
 * @brief Show every chain of infection by one patient
 * 
 * @param listPatient 
 * @param id 
 */
void patientsFOLLOW(PtList listPatient, long int id);

/**
 * @brief Show percent of patients by sex
 * 
 * @param listPatient 
 * @param sex 
 */
void patientsSEX(PtList listPatient, char *sex);

/**
 * @brief Insert an id and print a patient with the given id
 * 
 * @param listPatient 
 * @param id 
 */
void patientsSHOW(PtList listPatient, long int id);

/**
 * @brief Receives a list of patients and returns the 5 who took the longest to recover
 * 
 * @param listPatient 
 */
void patientsTOP5(PtList listPatient);

/**
 * @brief Receives a list of patients and shows the oldest of each sex
 * 
 * @param listPatient 
 */
void patientsOLDEST(PtList listPatient);