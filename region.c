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

int regionDestroy(PtRegion *r) {

    PtRegion region = *r;

    if(region == NULL) return REGION_NULL;

    free(region);
    *r = NULL;

    return REGION_OK;
}

void regionPrint(PtRegion r) {

    if(r == NULL) {

        printf("(NULL)\n");

    } else {
        // %-4ld | %-6s | %-4d | %-10s \t| %-10s \t| %-10s \t| %ld
        printf("%-13s \t|%-8s \t|%-10d |%.2f\n", r->name, r->capital, r->population, r->area);

    }

}

int regionName(PtRegion r, char *name) {

    if(r == NULL) return REGION_NULL;

    memcpy(name, r->name, sizeof(r->name));

    return REGION_OK;
}

int regionCapital(PtRegion r, char *capital) {

    if(r == NULL) return REGION_NULL;

    memcpy(capital, r->capital, sizeof(r->capital));

    return REGION_OK;
}

int regionPopulation(PtRegion r, int *population) {

    if(r == NULL) return REGION_NULL;

    (*population) = r->population;

    return REGION_OK;
}

int regionArea(PtRegion r, float *area) {

    if(r == NULL) return REGION_NULL;

    (*area) = r->area;

    return REGION_OK;
}