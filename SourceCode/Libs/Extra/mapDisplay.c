#include "mapDisplay.h"

void drawBlock(uint8_t x, uint8_t y, uint16_t color){
    uint8_t startX = x * 9, startY = y * 9;
    for(int i = startY; i < (startY + 9); i++)
        {
            for(int j = startX; j < (startX + 9); j++)
            {
                NNXT_LCD_DrawPixel(i, j, color); // top
            }
        }
}
