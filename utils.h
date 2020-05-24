/**
 * @file utils.h
 * @brief Useful code (module)
 * @date 2020-05-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

// #include "list.h"

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

char** split(char *string, int nFields, const char *delim);

// /**
//  * @brief Import a file
//  * 
//  * @param filename 
//  * @param listKR 
//  */
// void importKahootReportsFromFile(char * filename, PtList *listKR);