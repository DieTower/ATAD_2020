/**
 * @file utils.h
 * @brief Useful code (module)
 * @date 2020-05-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "list.h"

/**
 * @brief Put every char in one char array in lowercase
 * 
 * @param str[in][out]
 */
void lowerCase(char *str);

/**
 * @brief Put every char in one char array in uppercase
 * 
 * @param str[in][out]
 */
void upperCase(char *str);

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
 * @brief Populate a patient list 
 * 
 * @param filename 
 * @param listPatient 
 */
void importPatientsFromFile(char * filename, PtList *listPatient);