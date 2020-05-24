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
 * @brief Create a region
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
 * @brief Destroy a region
 * 
 * @param r 
 * @return int 
 */
int regionDestroy(PtRegion *r);

/**
 * @brief Print a region
 * 
 * @param r 
 */
void regionPrint(PtRegion r);

/**
 * @brief Return a name from region
 * 
 * @param r [in]
 * @param name [out]
 * @return int 
 */
int regionName(PtRegion r, char *name);

/**
 * @brief Return a capital from region
 * 
 * @param r [in]
 * @param capital [out]
 * @return int 
 */
int regionCapital(PtRegion r, char *capital);

/**
 * @brief Return a population from region
 * 
 * @param r [in]
 * @param population [out]
 * @return int 
 */
int regionPopulation(PtRegion r, int *population);

/**
 * @brief Return a area from region
 * 
 * @param r [in]
 * @param area [out]
 * @return int 
 */
int regionArea(PtRegion r, float *area);