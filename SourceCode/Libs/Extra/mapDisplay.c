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

uint8_t* symbolTable = {&s_Symbol[0][0], &one_Symbol[0][0], &two_Symbol[0][0], &three_Symbol[0][0], &arrowDown_Symbol[0][0], &arrowDown_Symbol[0][0]};

typedef enum bitSymbols{
    start,
    one, 
    two, 
    three
};                    



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

void drawSymbol(uint8_t x, uint8_t y, bitSymbols s, uint16_t color){
    uint8_t startX = x * 9, startY = y * 9;
    uint8_t * arr = symbolTable[s];
    for(int i = startY; i < (startY + 9); i++)
        {
            for(int j = startX; j < (startX + 9); j++)
            {
                if(arr[i][j])
                    NNXT_LCD_DrawPixel(i, j, color); 
            }
    }
}

void printSymbol(uint8_t x, uint8_t y, uint8_t update)  {


}