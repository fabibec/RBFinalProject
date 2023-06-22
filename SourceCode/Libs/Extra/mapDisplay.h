#ifndef MAPDISPLAY_H_INCLUDED
#define MAPDISPLAY_H_INCLUDED

#include "types.h"



void drawBlock(uint8_t, uint8_t, uint16_t);
void drawSymbolStart(uint8_t, uint8_t, uint16_t);
void drawSymbolOne(uint8_t, uint8_t, uint16_t);
void drawSymbolTwo(uint8_t, uint8_t, uint16_t);
void drawSymbolThree(uint8_t, uint8_t, uint16_t);
void drawSymbolUp(uint8_t, uint8_t, uint16_t);
void drawSymbolDown(uint8_t, uint8_t, uint16_t);
void drawSymbolLeft(uint8_t, uint8_t, uint16_t);
void drawSymbolRight(uint8_t, uint8_t, uint16_t);

void printMap(char (*)[14], uint8_t, uint8_t);
void printRoute(uint8_t *, uint8_t);

void updateRoute(uint8_t *, uint8_t, uint8_t, direction, uint8_t);

#endif /* MAPDISPLAY_H_INCLUDED */
