#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include "nnxt.h"

typedef struct{
    // holds table position as 2 1D Indexes
    uint8_t index1;
    uint8_t index2;
} table;

typedef struct{
    bool visited;
    uint16_t distance; // distance to start
    uint8_t prev; // index of previous tile
} tile;

typedef enum{
    N,
    E,
    S,
    W
} direction;

#endif //TYPES_H
