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


/*bool isTablePosition(char c){
    return (c == '1' || c == '2' || c == '3');
}
bool isStartPosition(char c){
    return c == 'S';
}*/
/*void initTablesArray(table * tables){
    for (int i = 0; i < 3; ++i) {
        tables[i].index1 = UINT8_MAX;
        tables[i].index2 = UINT8_MAX;
    }
}*/


/*void fillTablePosition(table * tables, uint8_t tableIndex, uint8_t posX, uint8_t posY){
    if(tables[tableIndex].index1 == UINT8_MAX){
        tables[tableIndex].index1 = conv2Dto1D(posX, posY);
    } else {
        tables[tableIndex].index2 = conv2Dto1D(posX, posY);
    }
}*/


/*bool leftExists(uint8_t index){
    return index != 0 || index % 14 != 0;
}
bool rightExists(uint8_t index){
    return index != 196 - 1 || index % 14 != 13;
}
bool aboveExists(uint8_t index){
    return index >= 14;
}
bool belowExists(uint8_t index){
    return index <= 196 - 1 - 14;
}*/


// utility function for dijkstra - finds the next vertex that needs to be processed
/*uint8_t minDistance(tile * mapTiles){
    uint8_t minimal = UINT8_MAX;
    uint8_t minIndex;

    for (uint8_t index = 0; index < 196; index++){
        if (mapTiles[index].visited == false && mapTiles[index].distance <= minimal){
            minimal = mapTiles[index].distance;
            minIndex = index;
        }
    }

    return minIndex;
}*/
/*void exploreSurroundings(uint8_t index, uint8_t* adjacent){
    if(aboveExists(index)){
        adjacent[0] = index - 14;
    }
    if(belowExists(index)){
        adjacent[1] = index + 14;
    }
    if(leftExists(index)){
        adjacent[2] = index - 1;
    }
    if(rightExists(index)){
        adjacent[3] = index + 1;
    }
}*/


/*bool isCurve(uint8_t index1, uint8_t index2){
    uint8_t x1, x2, y1, y2;
    conv1Dto2D(index1, &x1, &y1);
    conv1Dto2D(index2, &x2, &y2);
    return (x1 != x2 && y1 != y2);
}*/

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
