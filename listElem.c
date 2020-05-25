/**
 * @file listElem.c
 * @brief Implements operations for ListElem.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include "listElem.h"
#include <stdio.h>

void listElemPrint(ListElem elem) {

	if(elem == NULL) {
        printf("(NULL)\n");
    } else {
        patientPrint(elem);
    }
}