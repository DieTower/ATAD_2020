/**
 * @file region.h
 * @author Rodrigo Costa
 * @author Nicole Vieira
 * @brief Region data module
 * @date 2020-05-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#define REGION_OK 0
#define REGION_NULL 1

struct region;
typedef struct region* PtRegion;

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
);

/**
 * @brief This function will destroy a given PtRegion by freeing memory
 * 
 * @param r 
 * @return int 
 */
int regionDestroy(PtRegion *r);

/**
 * @brief This function will print a given region
 * 
 * @param r 
 */
void regionPrint(PtRegion r);

/**
 * @brief This function will give a region name
 * 
 * @param r 
 * @param name 
 * @return int 
 */
int regionName(PtRegion r, char *name);

/**
 * @brief This function will give a region capital
 * 
 * @param r 
 * @param capital 
 * @return int 
 */
int regionCapital(PtRegion r, char *capital);

/**
 * @brief This function will give a region population
 * 
 * @param r [in]
 * @param population [out]
 * @return int 
 */
int regionPopulation(PtRegion r, int *population);

/**
 * @brief This function will give a region area
 * 
 * @param r [in]
 * @param area [out]
 * @return int 
 */
int regionArea(PtRegion r, float *area);