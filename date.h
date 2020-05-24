/**
 * @file patient.h
 * @author Rodrigo Costa
 * @author Nicole Vieira
 * @brief Date data module implementation
 * @date 2020-05-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#define DATE_OK 0
#define DATE_NULL 1

struct date;
typedef struct date* PtDate;

typedef struct date {
    unsigned int day, month, year;
} Date;

/**
 * @brief Create a date
 * 
 * @param day 
 * @param month 
 * @param year 
 * @return PtDate 
 */
PtDate dateCreate(
    unsigned int day,
    unsigned int month,
    unsigned int year
);

/**
 * @brief Destroy a date
 * 
 * @param d 
 * @return int 
 */
int dateDestroy(PtDate *d);

/**
 * @brief Print a date
 * 
 * @param d 
 */
void datePrint(PtDate d);

/**
 * @brief Return a day from PtDate
 * 
 * @param d [in] 
 * @param day [out]
 * @return int 
 */
int dateDay(PtDate d, int *day);

/**
 * @brief Return a month from PtDate
 * 
 * @param d [in]
 * @param month [out]
 * @return int 
 */
int dateMonth(PtDate d, int *month);

/**
 * @brief Return a year from PtDate
 * 
 * @param d [in]
 * @param year [out]
 * @return int 
 */
int dateYear(PtDate d, int *year);