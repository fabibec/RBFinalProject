#ifndef UTILS_H
#define UTILS_H

#include "types.h"

// get rid of extern global var
//extern table tables[];
extern tile mapTiles[];


/* use 1D as 2D and vise versa*/
uint8_t conv2Dto1D(uint8_t row, uint8_t col);
void conv1Dto2D(uint8_t index, uint8_t* row, uint8_t* col);


/* check if neighbor tiles exist */
bool leftExists(uint8_t index);
bool rightExists(uint8_t index);
bool aboveExists(uint8_t index);
bool belowExists(uint8_t index);


bool isStartPosition(char c);
bool isTablePosition(char c);


void initTablesArray(table *);
void fillTablePosition(table *, uint8_t tableIndex, uint8_t i, uint8_t j);


/* Dijkstra */
uint8_t minDistance();
void exploreSurroundings(uint8_t index, uint8_t* adjacent);


/* Driving */
direction headsTo(uint8_t currentIndex, uint8_t nextIndex);
int8_t turnDegrees(direction to, direction * roboDirection);
direction turnDirections(direction d, int8_t steps,bool clockwise);


/* Debug */
void clearLine(uint8_t);
void printText(uint8_t line, char *ptr);


#endif //UTILS_H
