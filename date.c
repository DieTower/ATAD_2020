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
    PtDate date = (PtDate)malloc(sizeof(Date));

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

int dateCheck(PtDate d1, PtDate d2) {
    
    if(d1 == NULL) return DATE_NULL;

    if(d2 == NULL) return DATE_NULL;

    if(d1->year > d2->year) return DATE_NULL;

    if(d1->month > d2->month) return DATE_NULL;

    if((d1->year == d2->year) && (d1->month == d2->month) && (d1->day >= d2->day)) return DATE_NULL;

    return DATE_OK;
}

int diffDates(PtDate d1, PtDate d2, int *diff) {

    if(d1 == NULL) return DATE_NULL;

    if(d2 == NULL) return DATE_NULL;

    // Check dates
    int error_code = dateCheck(d1, d2);
    if(error_code != 0) return DATE_NULL;

    // Days in each month
    int arrayMonthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    int daysInBegin = 0;
    int daysInEnd = 0;

    int countDays = 0;
    for(int i=d1->year; i<=d2->year; i++) {
        for(int j=d1->month-1; j<=d2->month-1; j++) {
            
            // If is the first search set the day in the mouth the search beginning
            if(countDays == 0) {
                daysInBegin = d1->day;
            } else {
                daysInBegin = 0;
            }

            // If is the last search set the day in the mouth the search ends
            if(j == d2->month-1) {
                daysInEnd = d2->day;
            } else {
                daysInEnd = arrayMonthDays[j];
            }

            for(int l=daysInBegin; l<=daysInEnd; l++) {
                countDays++;
            }
        }
    }

    *diff = countDays-1;
    return DATE_OK;
}

int biggestDate(PtDate d1, PtDate d2, PtDate *date) {

    if(d1 == NULL) return DATE_NULL;

    if(d2 == NULL) return DATE_NULL;

    PtDate biggestOne = d1;

    if(d1->year <= d2->year && d1->month <= d2->month) {

        if(d1->year == d2->year && d1->month == d2->month) {

            if(d1->day < d2->day) {

                biggestOne = d2;
            }

        } else if(d1->year <= d2->year && d1->month < d2->month) {
            
            biggestOne = d2;

        } else if(d1->year < d2->year) {
            
            biggestOne = d2;
        }
    }

    *date = biggestOne;

    return DATE_OK;
}