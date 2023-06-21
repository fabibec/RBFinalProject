#include "mapDisplay.h"
#include "utils.h"


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

uint8_t circle_Symbol[9][9] = {{0},
                          {0, 0, 0, 1, 1, 1, 0, 0, 0},
                          {0, 0, 1, 1, 1, 1, 1, 0, 0},
                          {0, 1, 1, 1, 1, 1, 1, 1, 0},
                          {0, 1, 1, 1, 1, 1, 1, 1, 0},
                          {0, 1, 1, 1, 1, 1, 1, 1, 0},
                          {0, 0, 1, 1, 1, 1, 1, 0, 0},
                          {0, 0, 0, 1, 1, 1, 0, 0, 0},
                          {0}};

//uint8_t *symbolTable[6][9][9] = {&s_Symbol, &one_Symbol, &two_Symbol, &three_Symbol, &arrowDown_Symbol, &arrowDown_Symbol};



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

void drawSymbolStart(uint8_t x, uint8_t y, uint16_t color){
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
void drawSymbolOne(uint8_t x, uint8_t y, uint16_t color){
    uint8_t startX = x * 9, startY = y * 9;
    for(int i = startY; i < (startY + 9); i++)
        {
            for(int j = startX; j < (startX + 9); j++)
            {
                if(one_Symbol[j-startX][i-startY])
                    NNXT_LCD_DrawPixel(i, j, color);
            }
    }
}
void drawSymbolTwo(uint8_t x, uint8_t y, uint16_t color){
    uint8_t startX = x * 9, startY = y * 9;
    for(int i = startY; i < (startY + 9); i++)
        {
            for(int j = startX; j < (startX + 9); j++)
            {
                if(two_Symbol[j-startX][i-startY])
                    NNXT_LCD_DrawPixel(i, j, color);
            }
    }
}
void drawSymbolThree(uint8_t x, uint8_t y, uint16_t color){
    uint8_t startX = x * 9, startY = y * 9;
    for(int i = startY; i < (startY + 9); i++)
        {
            for(int j = startX; j < (startX + 9); j++)
            {
                if(three_Symbol[j-startX][i-startY])
                    NNXT_LCD_DrawPixel(i, j, color);
            }
    }
}
void drawSymbolUp(uint8_t x, uint8_t y, uint16_t color){
    uint8_t startX = x * 9, startY = y * 9;
    for(int i = startY; i < (startY + 9); i++)
        {
            for(int j = startX; j < (startX + 9); j++)
            {
                if(arrowUp_Symbol[j-startX][i-startY])
                    NNXT_LCD_DrawPixel(i, j, color);
            }
    }
}
void drawSymbolDown(uint8_t x, uint8_t y, uint16_t color){
    uint8_t startX = x * 9, startY = y * 9;
    for(int i = startY; i < (startY + 9); i++)
        {
            for(int j = startX; j < (startX + 9); j++)
            {
                if(arrowDown_Symbol[j-startX][i-startY])
                    NNXT_LCD_DrawPixel(i, j, color);
            }
    }
}
void drawSymbolLeft(uint8_t x, uint8_t y, uint16_t color){
    uint8_t startX = x * 9, startY = y * 9;
    for(int i = startY; i < (startY + 9); i++)
        {
            for(int j = startX; j < (startX + 9); j++)
            {
                if(arrowUp_Symbol[i-startY][j-startX])
                    NNXT_LCD_DrawPixel(i, j, color);
            }
    }
}

void drawSymbolRight(uint8_t x, uint8_t y, uint16_t color){
    uint8_t startX = x * 9, startY = y * 9;
    for(int i = startY; i < (startY + 9); i++)
        {
            for(int j = startX; j < (startX + 9); j++)
            {
                if(arrowDown_Symbol[i-startY][j-startX])
                    NNXT_LCD_DrawPixel(i, j, color);
            }
    }
}

void drawSymbolCircle(uint8_t x, uint8_t y, uint16_t color){
    uint8_t startX = x * 9, startY = y * 9;
    for(int i = startY; i < (startY + 9); i++)
        {
            for(int j = startX; j < (startX + 9); j++)
            {
                if(circle_Symbol[i-startY][j-startX])
                    NNXT_LCD_DrawPixel(i, j, color);
                else
                    NNXT_LCD_DrawPixel(i, j, LCD_COLOR_WHITE);
            }
    }
}

void printMap(char (*mapStringMatrix)[14]){
    for(int i = 0; i < 14; ++i){
        for(int j = 0; j < 14; ++j){
            if(mapStringMatrix[i][j] == '#')
                drawBlock(i, j, LCD_COLOR_BLACK);
            else if(mapStringMatrix[i][j] == 'S')
                drawSymbolStart(i, j, 0x75C8);
            else if(mapStringMatrix[i][j] == '1')
                drawSymbolOne(i, j, 0x0371);
            else if(mapStringMatrix[i][j] == '2')
                drawSymbolTwo(i, j, 0x0371);
            else if(mapStringMatrix[i][j] == '3')
                drawSymbolThree(i, j, 0x0371);
        }
    }
}

uint8_t valInArray(uint8_t val, uint8_t* arr, uint8_t length){
    for(uint8_t i = (length -1); i < UINT8_MAX; --i){
        if(arr[i] == val)
            return 1;
    }
    return 0;
}

void printRouteToMap(uint8_t* route, uint8_t length, uint8_t currentStep, uint8_t toDesk, char (*mapStringMatrix)[14], const direction roboDirection){
    NNXT_LCD_Clear(LCD_COLOR_WHITE);
    if(toDesk)
        route += currentStep;
    else
        length = currentStep;

    uint8_t index;
    if(currentStep != length){
        for(int i = 0; i < 14; ++i){
            for(int j = 0; j < 14; ++j){
                index = conv2Dto1D(i, j);
                if(mapStringMatrix[i][j] == '#')
                    drawBlock(i, j, LCD_COLOR_BLACK);
                else if(mapStringMatrix[i][j] == 'S')
                    drawSymbolStart(i, j, 0x75C8);
                else if(mapStringMatrix[i][j] == '1')
                    drawSymbolOne(i, j, 0x0371);
                else if(mapStringMatrix[i][j] == '2')
                    drawSymbolTwo(i, j, 0x0371);
                else if(mapStringMatrix[i][j] == '3')
                    drawSymbolThree(i, j, 0x0371);
                else if(valInArray(index, route, length))
                    drawSymbolCircle(i, j, 0xB6F1);
            }
        }
    }
    uint8_t row, col;
    if(currentStep != 0 && toDesk){
        conv1Dto2D(*(route - 1), &row, &col);
        switch(roboDirection){
            case S:
                drawSymbolDown(row, col, 0x026C);
                break;
            case N:
                drawSymbolUp(row, col, 0x026C);
                break;
            case W:
                drawSymbolLeft(row, col, 0x026C);
                break;
            case E:
                drawSymbolRight(row, col, 0x026C);
                break;
        }

    }

}

void printRoute(uint8_t* route, uint8_t length){
    uint8_t index;
    for(int i = 0; i < 14; ++i){
        for(int j = 0; j < 14; ++j){
            index = conv2Dto1D(i, j);
            if(valInArray(index, route, length))
                drawSymbolCircle(i, j, 0xB6F1);
        }
    }
}

void updateRoute(uint8_t* route, uint8_t routeLength, uint8_t currentIndex, direction* roboDir){
    uint8_t row, col;
    for(int i = 0; i < currentIndex; i++){
            conv1Dto2D(route[i], &row, &col);
            drawBlock(row, col, LCD_COLOR_WHITE);
    }

    conv1Dto2D(route[currentIndex - 1], &row, &col);
    if(currentIndex != 0)
        switch(*roboDir){
                case S:
                    drawSymbolDown(row, col, 0x026C);
                    break;
                case N:
                    drawSymbolUp(row, col, 0x026C);
                    break;
                case W:
                    drawSymbolLeft(row, col, 0x026C);
                    break;
                case E:
                    drawSymbolRight(row, col, 0x026C);
                    break;
        }
}
