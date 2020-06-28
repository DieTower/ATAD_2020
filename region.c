/**
 * @file region.c
 * @author Rodrigo Costa
 * @author Nicole Vieira
 * @brief Region data module
 * @date 2020-05-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "region.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct region {
    char name[40];
    char capital[40];
    int population;
    float area;
} Region;

/**
 * @brief This function will create a PtRegion by allocation memory with malloc
 * If the allocation is successfull the values will be empty
 * 
 * @param name 
 * @param capital 
 * @param population 
 * @param area 
 * @return PtRegion 
 */
PtRegion regionCreate(
    char name[40],
    char capital[40],
    int population,
    float area
) {
    PtRegion region = (PtRegion) malloc(sizeof(Region));

    if(region == NULL) return NULL;

    memcpy(region->name, name, sizeof(region->name));
    memcpy(region->capital, capital, sizeof(region->capital));
    region->population = population;
    region->area = area;

    return region;
}

/**
 * @brief This function will destroy a given PtRegion by freeing memory
 * 
 * @param r 
 * @return int 
 */
int regionDestroy(PtRegion *r) {

    PtRegion region = *r;

    if(region == NULL) return REGION_NULL;

    free(region);
    *r = NULL;

    return REGION_OK;
}

/**
 * @brief This function will print a given region
 * 
 * @param r 
 */
void regionPrint(PtRegion r) {

    if(r == NULL) {

        printf("(NULL)\n");

    } else {
        // %-4ld | %-6s | %-4d | %-10s \t| %-10s \t| %-10s \t| %ld
        printf("%-13s \t|%-8s \t|%-10d |%.2f\n", r->name, r->capital, r->population, r->area);

    }

}

/**
 * @brief This function will give a region name
 * 
 * @param r 
 * @param name 
 * @return int 
 */
int regionName(PtRegion r, char *name) {

    if(r == NULL) return REGION_NULL;

    memcpy(name, r->name, sizeof(r->name));

    return REGION_OK;
}

/**
 * @brief This function will give a region capital
 * 
 * @param r 
 * @param capital 
 * @return int 
 */
int regionCapital(PtRegion r, char *capital) {

    if(r == NULL) return REGION_NULL;

    memcpy(capital, r->capital, sizeof(r->capital));

    return REGION_OK;
}

/**
 * @brief This function will give a region population
 * 
 * @param r 
 * @param population 
 * @return int 
 */
int regionPopulation(PtRegion r, int *population) {

    if(r == NULL) return REGION_NULL;

    (*population) = r->population;

    return REGION_OK;
}

/**
 * @brief This function will give a region area
 * 
 * @param r 
 * @param area 
 * @return int 
 */
int regionArea(PtRegion r, float *area) {

    if(r == NULL) return REGION_NULL;

    (*area) = r->area;

    return REGION_OK;
}