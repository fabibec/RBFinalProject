#ifndef matrixUtils_H
#define matrixUtils_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t x;
    uint8_t y;
} coord; 

char mapStringMatrix[14][14];

coord tablePositionArray[3][2] = {{{0 ,0}, {0, 0}}, {{0, 0}, {0, 0}}, {{0, 0}, {0, 0}}};
                                
coord startPosition = {0, 0};


void convertMapStringToMatrix();
void printStringMatrix();
void findTableAndStartPosition();
void printTableAndStartPosition();

bool checkField(int8_t x, int8_t y);
bool checkAbove(coord*);
bool checkBelow(coord*);
bool checkLeft(coord*);
bool checkRight(coord*);

bool isStartPosition(char);
bool isTablePosition(char);
bool tableNotFoundYet(char);

#endif
