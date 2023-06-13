#ifndef CODEINPROGRESS_UTILS_H
#define CODEINPROGRESS_UTILS_H
#include <stdint.h>
#include <stdbool.h>
#include "types.h"

extern table tables[];
extern tile mapTiles[];

/* use 1D as 2D and vise versa*/
uint8_t conv2Dto1D(uint8_t row, uint8_t col);
void conv1Dto2D(uint8_t index, uint8_t* row, uint8_t* col);

/* check if neighbor tiles exist */
bool leftExits(uint8_t index);
bool rightExits(uint8_t index);
bool aboveExits(uint8_t index);
bool belowExits(uint8_t index);

bool isStartPosition(char c);
bool isTablePosition(char c);

void initTablesArray();
void fillTablePosition(uint8_t tableIndex, uint8_t i, uint8_t j);

/* Dijkstra */
uint8_t minDistance();
void exploreSurroundings(uint8_t index, uint8_t* adjacent);

#endif //CODEINPROGRESS_UTILS_H
