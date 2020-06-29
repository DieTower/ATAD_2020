/**
 * @file stringCode.h
 * @author Nicole Vieira
 * @author Rodrigo Costa
 * @brief Defines a string to use in maps
 * @version 0.1
 * @date 2020-06-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

typedef struct stringCode{
    char code[256];
} StringCode;

/**
 * @brief This function will create a string code and return it
 * 
 * @param str 
 * @return StringCode 
 */
StringCode stringCodeCreate(char *str);

/**
 * @brief This function will print a given string code
 * 
 * @param strCode 
 */
void stringCodePrint(StringCode strCode);