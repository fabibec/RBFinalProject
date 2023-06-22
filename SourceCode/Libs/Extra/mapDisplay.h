#ifndef MAPDISPLAY_H_INCLUDED
#define MAPDISPLAY_H_INCLUDED

#include "types.h"

typedef enum{
    ROBOT_COLOR = 0x5C54,
    OBSTACLE_COLOR = 0x530D,
    ROUTE_COLOR = 0xAFE6,
    NO_DEST_COLOR = 0xD9E5,
    DEST_COLOR = 0x0653
} DISPLAY_COLORS;

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
