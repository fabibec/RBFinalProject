#ifndef UTILS_H
#define UTILS_H

#include "types.h"

// get rid of extern global var
//extern table tables[];
//extern tile mapTiles[];


/* use 1D as 2D and vise versa*/
uint8_t conv2Dto1D(const uint8_t, const uint8_t);
void conv1Dto2D(const uint8_t, uint8_t *, uint8_t *);


/* check if neighbor tiles exist */
//bool leftExists(uint8_t index);
//bool rightExists(uint8_t index);
//bool aboveExists(uint8_t index);
//bool belowExists(uint8_t index);


//bool isStartPosition(char c);
//bool isTablePosition(char c);


//void initTablesArray(table *);
//void fillTablePosition(table *, uint8_t tableIndex, uint8_t i, uint8_t j);


/* Dijkstra */
//uint8_t minDistance(tile *);
//void exploreSurroundings(uint8_t index, uint8_t* adjacent);


/* Driving */
direction headsTo(const uint8_t, const uint8_t);
int8_t turnDegrees(const direction, const direction);
direction turnDirections(const direction, const int8_t, const bool);


/* Debug */
void clearLine(const uint8_t);
void printText(const uint8_t, char *);


#endif //UTILS_H
