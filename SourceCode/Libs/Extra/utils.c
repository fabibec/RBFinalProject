#include "utils.h"
#include "motion.h"


void clearLine(const uint8_t line){
    NNXT_LCD_ClearStringLine((uint16_t)line);
}
void printText(const uint8_t line, char *ptr){
    clearLine(line);
    NNXT_LCD_DisplayStringAtLine(line, ptr);
}


uint8_t conv2Dto1D(const uint8_t row, const uint8_t col){
    return row * 14 + col;
}
void conv1Dto2D(const uint8_t index, uint8_t* row, uint8_t* col){
    *row = index / 14;
    *col = index % 14;
}


direction headsTo(const uint8_t currentIndex, const uint8_t nextIndex){
    uint8_t x1, x2, y1, y2;

    // TODO change parameter from y,x to x,y ?
    conv1Dto2D(currentIndex, &y1, &x1);
    conv1Dto2D(nextIndex, &y2, &x2);

    if((x1 + 1) == x2){
        return E;
    } else if ((x1 - 1) == x2){
        return W;
    } else if ((y1 - 1) == y2){
        return N;
    } else {
        return S;
    }
}
bool enumUnderflow(const direction d){
    return ((uint8_t) d - 1) < 0;
}
direction turnDirections(const direction d, const int8_t steps, const bool clockwise){
    direction newDir = d;
    for (int8_t i = 0; i < steps; ++i) {
        if(clockwise){
            newDir = ((newDir + 1) % 4);
        } else{
            if(!enumUnderflow(newDir))
                newDir--;
            else
                newDir = 3;
        }
    }
    return newDir;
}
// -1 left Turn; 0 no turn; 1 right Turn; 2 180 deg
int8_t turnDegrees(const direction turnsTo, const direction roboDirection){
    direction currentDirection = roboDirection;

    if(((currentDirection + 1) % 4) == turnsTo)
        return 1;
    else if(turnDirections(currentDirection, 1, false) == turnsTo)
        return -1;
    else if(turnDirections(currentDirection, 2, true) == turnsTo)
        return 2;
    else
        return 0;
}
