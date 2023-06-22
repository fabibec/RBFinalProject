#include "dijkstra.h"
#include "utils.h"


char mapStringMatrix[14][14];
uint8_t start;
uint8_t destinations[] = {1, 2};
table tables[3];
tile mapTiles[196];
uint8_t closestDestTiles[2];


char ** getMapStringMatrix(){
    return mapStringMatrix;
}
uint8_t getStart(){
    return start;
}
tile * getMapTiles(){
    return mapTiles;
}
uint8_t getDestTile(uint8_t index){
    return closestDestTiles[index];
}
uint8_t getDestTablesAtIndex(uint8_t index){
    return destinations[index];
}

void initDijkstra(){
    initMapTiles();
    initTablesArray();
}
void initMapTiles(){
    for(uint8_t i = 0; i < 196; ++i){
        mapTiles[i].visited = false;
        mapTiles[i].distance = UINT8_MAX;
        mapTiles[i].prev = i;
    }
}
void initTablesArray(){
    for (int i = 0; i < 3; ++i) {
        tables[i].index1 = UINT8_MAX;
        tables[i].index2 = UINT8_MAX;
    }
}


void convertMapStringToMatrix(){
    /*const char* mapString = "\
##############\
# S          #\
######       #\
#    #       #\
#            #\
# 11 ######  #\
######       #\
#       ######\
##### #      #\
#33   ###### #\
#     #      #\
#     #    22#\
#     #      #\
##############";*/

    const char* mapString = "###############     S      ###   #####   ##    11      ##            ##   ####   2 ##      #   2 ##      #     ##   ###########   #        ##   #   33   ##   #        ##            ###############";

    for (uint8_t i = 0; i < 196; i++) {
        mapStringMatrix[(i/14)][(i%14)] = mapString[i];
    }
}


void findStartAndTablePosition(){
    char currentChar = 0;
    uint8_t tableIndex = UINT8_MAX;

    for (int8_t i = 1; i < 13; i++){
        for (int8_t j = 1; j < 13; j++) {
            currentChar = mapStringMatrix[i][j];
            if (isStartPosition(currentChar)) {
                start = conv2Dto1D(i,j);
            } else if (isTablePosition(currentChar)){
                tableIndex = (currentChar - '1');
                fillTablePosition(tableIndex, i, j);
            }
        }
    }
}
bool isTablePosition(char c){
    return (c == '1' || c == '2' || c == '3');
}
bool isStartPosition(char c){
    return c == 'S';
}
void fillTablePosition(uint8_t tableIndex, uint8_t posX, uint8_t posY){
    if(tables[tableIndex].index1 == UINT8_MAX){
        tables[tableIndex].index1 = conv2Dto1D(posX, posY);
    } else {
        tables[tableIndex].index2 = conv2Dto1D(posX, posY);
    }
}


void dijkstra(){
    mapTiles[start].distance = 0;

    for (uint8_t i = 0; i < 196 - 1; ++i){
        uint8_t x, y;
        uint8_t minIndex = minDistance(mapTiles);
        uint8_t adjacent[4] = {UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX};

        mapTiles[minIndex].visited = true;
        exploreSurroundings(minIndex, adjacent);

        for(uint8_t j = 0; j < 4; ++j){
            if(adjacent[j] != UINT8_MAX){
                conv1Dto2D(adjacent[j], &x, &y);

                if(mapStringMatrix[x][y] != ' ')
                    continue;
                if(mapTiles[minIndex].distance == UINT8_MAX)
                    continue;
                if(mapTiles[j].visited)
                    continue;
                if((mapTiles[minIndex].distance + 1) >= mapTiles[adjacent[j]].distance)
                    continue;

                mapTiles[adjacent[j]].distance = mapTiles[minIndex].distance + 1;
                mapTiles[adjacent[j]].prev = minIndex;
            }
        }
    }
}
uint8_t minDistance(){
    uint8_t minimal = UINT8_MAX;
    uint8_t minIndex = UINT8_MAX;

    for (uint8_t index = 0; index < 196; index++){
        if (mapTiles[index].visited == false && mapTiles[index].distance <= minimal){
            minimal = mapTiles[index].distance;
            minIndex = index;
        }
    }

    return minIndex;
}
void exploreSurroundings(uint8_t index, uint8_t * adjacent){
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
}
bool leftExists(uint8_t index){
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
}


void findClosestTableTile(uint8_t index){
    uint8_t minDist1, minDist2, index1, index2;

    findClosestTile(tables[destinations[index] - 1].index1, &index1, &minDist1);
    findClosestTile(tables[destinations[index] - 1].index2, &index2, &minDist2);

    closestDestTiles[index] = (minDist1 < minDist2) ? index1 : index2;
}
void findClosestTile(uint8_t tableIndex, uint8_t * lowestTableIndex, uint8_t * lowestDistance){
    uint8_t currentMinDistance = UINT8_MAX;
    uint8_t x, y;

    conv1Dto2D(tableIndex, &x, &y);

    for (uint16_t row = (x - 1); row <= (x + 1); ++row) {
        for (uint16_t col = (y - 1); col <= (y + 1); ++col) {
            if((x < 0 || y < 0 || x >= 14 || y >= 14))
                continue;
            if(mapTiles[conv2Dto1D(row, col)].distance >= currentMinDistance)
                continue;

            *lowestTableIndex = conv2Dto1D(row, col);
            currentMinDistance = mapTiles[conv2Dto1D(row, col)].distance;
        }
    }

    *lowestDistance = currentMinDistance;
}
