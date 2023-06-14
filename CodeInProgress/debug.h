//
// Created by fabi on 12.06.23.
//
#ifndef CODEINPROGRESS_DEBUG_H
#define CODEINPROGRESS_DEBUG_H
#include <stdint.h>
#include "types.h"

extern uint8_t start;
extern char mapStringMatrix[14][14];
extern table tables[];
extern tile mapTiles[];

void printStartAndTablePosition();
void printSolution();
void printSolutionMatrix();

#endif //CODEINPROGRESS_DEBUG_H
