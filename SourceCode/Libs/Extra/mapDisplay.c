#include "mapDisplay.h"

uint8_t s_Symbol[9][9] = {{0},
                          {0, 0, 0, 1, 1, 1, 0, 0, 0},
                          {0, 0, 1, 0, 0, 0, 1, 0, 0},
                          {0, 0, 0, 1, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 1, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 1, 0, 0, 0},
                          {0, 0, 1, 0, 0, 0, 1, 0, 0},
                          {0, 0, 0, 1, 1, 1, 0, 0, 0},
                          {0}};

uint8_t one_Symbol[9][9] = {{0},
                          {0, 0, 0, 0, 1, 0, 0, 0, 0},
                          {0, 0, 0, 1, 1, 0, 0, 0, 0},
                          {0, 0, 0, 0, 1, 0, 0, 0, 0},
                          {0, 0, 0, 0, 1, 0, 0, 0, 0},
                          {0, 0, 0, 0, 1, 0, 0, 0, 0},
                          {0, 0, 0, 0, 1, 0, 0, 0, 0},
                          {0, 0, 0, 1, 1, 1, 0, 0, 0},
                          {0}};

uint8_t two_Symbol[9][9] = {{0},
                          {0, 0, 0, 1, 1, 1, 0, 0, 0},
                          {0, 0, 1, 0, 0, 0, 1, 0, 0},
                          {0, 0, 0, 0, 0, 0, 1, 0, 0},
                          {0, 0, 0, 1, 1, 1, 0, 0, 0},
                          {0, 0, 1, 0, 0, 0, 0, 0, 0},
                          {0, 0, 1, 0, 0, 0, 0, 0, 0},
                          {0, 0, 1, 1, 1, 1, 1, 0, 0},
                          {0}};

uint8_t three_Symbol[9][9] = {{0},
                          {0, 0, 0, 1, 1, 1, 0, 0, 0},
                          {0, 0, 1, 0, 0, 0, 1, 0, 0},
                          {0, 0, 0, 0, 0, 0, 1, 0, 0},
                          {0, 0, 0, 1, 1, 1, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 1, 0, 0},
                          {0, 0, 1, 0, 0, 0, 1, 0, 0},
                          {0, 0, 0, 1, 1, 1, 0, 0, 0},
                          {0}};

uint8_t arrowDown_Symbol[9][9] = {{0},
                          {0, 0, 0, 0, 1, 0, 0, 0, 0},
                          {0, 0, 0, 0, 1, 0, 0, 0, 0},
                          {0, 0, 0, 0, 1, 0, 0, 0, 0},
                          {0, 0, 0, 0, 1, 0, 0, 0, 0},
                          {0, 0, 1, 1, 1, 1, 1, 0, 0},
                          {0, 0, 0, 1, 1, 1, 0, 0, 0},
                          {0, 0, 0, 0, 1, 0, 0, 0, 0},
                          {0}};

uint8_t arrowUp_Symbol[9][9] = {{0},
                          {0, 0, 0, 0, 1, 0, 0, 0, 0},
                          {0, 0, 0, 1, 1, 1, 0, 0, 0},
                          {0, 0, 1, 1, 1, 1, 1, 0, 0},
                          {0, 0, 0, 0, 1, 0, 0, 0, 0},
                          {0, 0, 0, 0, 1, 0, 0, 0, 0},
                          {0, 0, 0, 0, 1, 0, 0, 0, 0},
                          {0, 0, 0, 0, 1, 0, 0, 0, 0},
                          {0}};

uint8_t ***symbolTable = {s_Symbol, one_Symbol, two_Symbol, three_Symbol, arrowDown_Symbol, arrowDown_Symbol};



void drawBlock(uint8_t x, uint8_t y, uint16_t color){
    uint8_t startX = x * 9, startY = y * 9;
    for(int i = startY; i < (startY + 9); i++)
        {
            for(int j = startX; j < (startX + 9); j++)
            {
                NNXT_LCD_DrawPixel(i, j, color);
            }
    }
}

void drawSymbol(uint8_t x, uint8_t y, bitSymbol s, uint16_t color){
    uint8_t ** currentArr = symbolTable[s];
    uint8_t startX = x * 9, startY = y * 9;
    for(int i = startY; i < (startY + 9); i++)
        {
            for(int j = startX; j < (startX + 9); j++)
            {
                if(currentArr[j-startX][i-startY])
                    NNXT_LCD_DrawPixel(i, j, color);
            }
    }
}

void drawS(uint8_t x, uint8_t y, uint16_t color)
{
    uint8_t startX = x * 9, startY = y * 9;
    for(int i = startY; i < (startY + 9); i++)
        {
            for(int j = startX; j < (startX + 9); j++)
            {
                if(s_Symbol[j-startX][i-startY])
                    NNXT_LCD_DrawPixel(i, j, color);
            }
    }
}
