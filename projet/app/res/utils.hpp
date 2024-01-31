#ifndef UTILS_H
#define UTILS_H
#include <string.h>
#include <stdint.h>


bool compareCharArrays(const char* array1, const char* array2) {

    uint8_t size = (uint8_t) strlen(array1);
    for (uint8_t i = 0; i < size; ++i) {
        if (array1[i] != array2[i]) {
            return false;
        }
    }
    return true;
}

#endif