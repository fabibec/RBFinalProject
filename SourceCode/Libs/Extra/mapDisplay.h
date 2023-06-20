#ifndef MAPDISPLAY_H_INCLUDED
#define MAPDISPLAY_H_INCLUDED

#include "nnxt.h"

typedef enum{
    _start,
    one,
    two,
    three
} bitSymbol;


void drawBlock(uint8_t x, uint8_t y, uint16_t color);

void drawSymbol(uint8_t x, uint8_t y, bitSymbol s, uint16_t color);
void drawS(uint8_t x, uint8_t y, uint16_t color);

#endif /* MAPDISPLAY_H_INCLUDED */
