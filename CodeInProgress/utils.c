#include "utils.h"
#include "motion.h"


uint8_t conv2Dto1D(uint8_t row, uint8_t col){
    return row * 14 + col;
}

void conv1Dto2D(uint8_t index, uint8_t* row, uint8_t* col){
    *row = index / 14;
    *col = index % 14;
}

bool isTablePosition(char c){
    return (c == '1' || c == '2' || c == '3');
}

bool isStartPosition(char c){
    return c == 'S';
}
void initTablesArray(){
    for (int i = 0; i < 3; ++i) {
        tables[i].index1 = UINT8_MAX;
        tables[i].index2 = UINT8_MAX;
    }
}

void fillTablePosition(uint8_t tableIndex, uint8_t i, uint8_t j){
    if(tables[tableIndex].index1 == UINT8_MAX){
        tables[tableIndex].index1 = conv2Dto1D(i, j);
    } else {
        tables[tableIndex].index2 = conv2Dto1D(i, j);
    }
}

bool leftExits(uint8_t index){
    return index != 0 || index % 14 != 0;
}

bool rightExits(uint8_t index){
    return index != 196 - 1 || index % 14 != 13;
}

bool aboveExits(uint8_t index){
    return index >= 14;
}

bool belowExits(uint8_t index){
    return index <= 196 - 1 - 14;
}

// utility function for dijkstra - finds the next vertex the needs to be processed
uint8_t minDistance(){
    uint8_t min = UINT8_MAX;
    uint8_t min_index;

    for (uint8_t v = 0; v < 196; v++)
        if (mapTiles[v].visited == false && mapTiles[v].distance <= min)
            min = mapTiles[v].distance, min_index = v;

    return min_index;
}

void exploreSurroundings(uint8_t index, uint8_t* adjacent){
    if(aboveExits(index)){
        adjacent[0] = index - 14;
    }
    if(belowExits(index)){
        adjacent[1] = index + 14;
    }
    if(leftExits(index)){
        adjacent[2] = index - 1;
    }
    if(rightExits(index)){
        adjacent[3] = index + 1;
    }
}


bool isCurve(uint8_t index1, uint8_t index2){
    uint8_t x1, x2, y1, y2;
    conv1Dto2D(index1, &x1, &y1);
    conv1Dto2D(index2, &x2, &y2);
    return (x1 != x2 && y1 != y2);
}

direction headsTo(uint8_t currentIndex, uint8_t nextIndex){
    uint8_t x1, x2, y1, y2;
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

// -1 left Turn; 0 no turn; 1 right Turn
int8_t turnDegrees(direction to){
    direction currentDirection = roboDirection;
    if((currentDirection + 1 % 4) == to){
        return 1;
    } else if (currentDirection == N && to == W ){
        return -1;
    }
    else if((currentDirection - 1 % 4) == to){
        return -1;
    }
    return 0;
}

void setRoboDir(direction d){
    roboDirection = d;
}

direction getRoboDir(){
    return roboDirection;
}