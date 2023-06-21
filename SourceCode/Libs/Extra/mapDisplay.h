#ifndef MAPDISPLAY_H_INCLUDED
#define MAPDISPLAY_H_INCLUDED

#include "types.h"


typedef enum{
    _start,
    one,
    two,
    three
} bitSymbol;


void drawBlock(uint8_t x, uint8_t y, uint16_t color);
void drawSymbolStart(uint8_t x, uint8_t y, uint16_t color);
void drawSymbolOne(uint8_t x, uint8_t y, uint16_t color);
void drawSymbolTwo(uint8_t x, uint8_t y, uint16_t color);
void drawSymbolThree(uint8_t x, uint8_t y, uint16_t color);
void drawSymbolUp(uint8_t x, uint8_t y, uint16_t color);
void drawSymbolDown(uint8_t x, uint8_t y, uint16_t color);
void drawSymbolLeft(uint8_t x, uint8_t y, uint16_t color);
void drawSymbolRight(uint8_t x, uint8_t y, uint16_t color);
void printMap(char (*)[14]);
void printRoute(uint8_t* route, uint8_t length);
void printRouteToMap(uint8_t* route, uint8_t size, uint8_t currentStep, uint8_t toDesk, char (*)[14], const direction);
void updateRoute(uint8_t* route, uint8_t routelLength, uint8_t currentIndex, direction roboDir, uint8_t toDesk);

#endif /* MAPDISPLAY_H_INCLUDED */
