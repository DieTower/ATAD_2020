/**
 * @file mapElem.c
 * @brief Implements operations for types MapKey and MapValue.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include "mapElem.h"
#include <stdio.h>
#include <string.h>

void mapKeyPrint(MapKey key) {
	printf("%s\n", key);
}

void mapValuePrint(MapValue value) {
    
	if(value == NULL) {
        printf("(NULL)\n");
    } else {
        regionPrint(value);
    }
}

bool mapKeyEquals(MapKey key1, MapKey key2) {
	// in case of string keys:
    // printf("Key1: %s --- Key2: %s\n", key1, key2);
    if(strcmp(key1, key2) == 0) {
        // printf("Super true\n");
        return true;
    } else {
        // printf("Super false\n\n");
        return false;
    }
}