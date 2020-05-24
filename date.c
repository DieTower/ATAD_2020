/**
 * @file date.c
 * @author Rodrigo Costa
 * @author Nicole Vieira
 * @brief Date data module implementation
 * @date 2020-05-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "date.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PtDate dateCreate(
    unsigned int day,
    unsigned int month,
    unsigned int year
) {
    PtDate date = (PtDate) malloc(sizeof(Date));

    if(date == NULL) return NULL;
    
    date->day = day;
    date->month = month;
    date->year = year;

    return date;
}

int dateDestroy(PtDate *d) {

    PtDate date = *d;

    if(date == NULL) return DATE_NULL;

    free(date);
    *d = NULL;

    return DATE_OK;
}

void datePrint(PtDate d) {

    if(d == NULL) {

        printf("(NULL)\n");

    } else {

        printf("%02d-%02d-%-4d\n", d->day, d->month, d->year);

    }

}

int dateDay(PtDate d, int *day) {

    if(d == NULL) return DATE_NULL;

    (*day) = d->day;

    return DATE_OK;
}

int dateMonth(PtDate d, int *month) {

    if(d == NULL) return DATE_NULL;

    (*month) = d->month;

    return DATE_OK;
}

int dateYear(PtDate d, int *year) {

    if(d == NULL) return DATE_NULL;

    (*year) = d->year;

    return DATE_OK;
}