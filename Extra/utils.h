#ifndef UTILS_H
#define UTILS_H

#include "types.h"

extern table tables[];
extern tile mapTiles[];
extern direction roboDirection;

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

direction headsTo(uint8_t currentIndex, uint8_t nextIndex);
int8_t turnDegrees(direction to);
void setRoboDir(direction d);
direction getRoboDir();
direction turnDirections(direction d, int8_t steps,bool clockwise);


void clearLine(uint8_t);

void printText(uint8_t line, char *ptr);


#endif //CODEINPROGRESS_UTILS_H
