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
 * @brief This function will create a new date with the memory allocation type malloc
 * If the allocation is unsuccessful the null value will be returned
 * Else a new PtDate is returned
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
 * @brief This function will destroy a PtDate thereby freeing up memory
 * If the date is null the null value will be returned
 * Else a ok value will be returned
 * 
 * @param d 
 * @return int 
 */
int dateDestroy(PtDate *d);

/**
 * @brief This function will print the date in the format ex:(22-03-1956)
 * 
 * @param d 
 */
void datePrint(PtDate d);

/**
 * @brief This function will return the day from the given date
 * If the date is null the null value will be returned
 * Else the ok value will be returned
 * 
 * @param d [in]
 * @param day [out]
 * @return int 
 */
int dateDay(PtDate d, int *day);

/**
 * @brief This function will return the month from the given date
 * If the date is null the null value will be returned
 * Else the ok value will be returned
 * 
 * @param d [in]
 * @param month [out]
 * @return int 
 */
int dateMonth(PtDate d, int *month);

/**
 * @brief This function will return the year from the given date
 * If the date is null the null value will be returned
 * Else the ok value will be returned
 * 
 * @param d [in]
 * @param year [out]
 * @return int 
 */
int dateYear(PtDate d, int *year);

/**
 * @brief This function will receive two dates and give the difference in days between them
 * If any of the dates are invalid the null value will return
 * Else will convert the date difference to days
 * Finally the ok valye will return
 * 
 * @param d1 [in]
 * @param d2 [in]
 * @param diff [out]
 * @return int 
 */
int diffDates(PtDate d1, PtDate d2, int *diff);

/**
 * @brief This function will verify which one of the two is the biggest
 * The two dates will be verified if they are valid
 * Then a new date is created in order to save the biggest date
 * Finally the ok value will return
 * 
 * @param d1 [in]
 * @param d2 [in]
 * @param date [out]
 * @return int 
 */
int biggestDate(PtDate d1, PtDate d2, PtDate *date);