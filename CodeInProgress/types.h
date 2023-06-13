#ifndef CODEINPROGRESS_TYPES_H
#define CODEINPROGRESS_TYPES_H
#include "stdint.h"
#include "stdbool.h"

typedef struct {
    // holds table position as 2 1D Indexes
    uint8_t index1;
    uint8_t index2;
} table;

typedef struct{
    bool visited;
    uint16_t distance; // distance to start
    uint8_t prev; //address of previous
} tile;

#endif //CODEINPROGRESS_TYPES_H
