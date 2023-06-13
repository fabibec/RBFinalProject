#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "utils.h"
#include "types.h"
#include "debug.h"

/* Matrix conversion */
char mapStringMatrix[14][14];

void convertMapStringToMatrix(){
    const char* mapString = "###############     S      ###   #####   ##    11      ##            ##   ####   2 ##      #   2 ##      #     ##   ###########   #        ##   #   33   ##   #        ##            ###############";

    for (uint8_t i = 0; i < 196; i++) {
        mapStringMatrix[(i/14)][(i%14)] = mapString[i];
    }
}
/* Matrix conversion End*/

/* Tracking start and possible end positions */

uint8_t destinations[] = {2, 3};
// start index is stored as 1D index
uint8_t start;
// holds the tables positions at index [table name (either 1,2 or 3) - 1]
table tables[3];

void findStartAndTablePosition(){

    initTablesArray();

    char currentChar;
    uint8_t x;
    for (int8_t i = 1; i < 13; i++){
        for (int8_t j = 1; j < 13; j++) {
            currentChar = mapStringMatrix[i][j];
            if (isStartPosition(currentChar)) {
                start = conv2Dto1D(i,j);
            } else if (isTablePosition(currentChar)){
                x = (currentChar - '1');
                fillTablePosition(x, i, j);        
            }
        }
    }
}
/* Tracking start and possible end positions - end */

/* Dijkstra Pathfinding */
tile mapTiles[196];
uint8_t closestDestTiles[2];

void dijkstra(){
    for(uint8_t i = 0; i < 196; ++i){
        mapTiles[i].visited = false;
        mapTiles[i].distance = UINT8_MAX;
        mapTiles[i].prev = i;
    }
    mapTiles[start].distance = 0;

    for (uint8_t count = 0; count < 196 - 1; count++) {
        uint8_t u = minDistance();

        mapTiles[u].visited = true;

        uint8_t adjacent[4] = {UINT8_MAX, UINT8_MAX, UINT8_MAX,UINT8_MAX};
        exploreSurroundings(u, &adjacent[0]);

        uint8_t x, y;
        for(uint8_t v = 0; v < 4; v++){
            if(adjacent[v] != UINT8_MAX){
                conv1Dto2D(adjacent[v], &x, &y);
                if (mapStringMatrix[x][y] == ' '
                    && mapTiles[u].distance != UINT8_MAX
                    && !mapTiles[v].visited
                    && (mapTiles[u].distance + 1) < mapTiles[adjacent[v]].distance){
                    mapTiles[adjacent[v]].distance = mapTiles[u].distance + 1;
                    mapTiles[adjacent[v]].prev = u;
                }
            }
        }
    }
}

void findClosestTile(uint8_t tableIndex, uint8_t* lowestTableIndex, uint8_t* lowestDistance){
    uint8_t currentMinDistance = UINT8_MAX, index, x, y;
    conv1Dto2D(tableIndex, &x, &y);
    for (uint16_t row = (x - 1); row <= (x + 1); ++row) {
        for (uint16_t col = (y - 1); col <= (y + 1); ++col) {
            if(!(x < 0 || y < 0 || x >= 14 || y >= 14) && mapTiles[conv2Dto1D(row, col)].distance < currentMinDistance){
                index = conv2Dto1D(row, col);
                currentMinDistance = mapTiles[index].distance;
                *lowestTableIndex = index;
            }
        }
    }
    *lowestDistance = currentMinDistance;
}

void findClosestTableTile(table* t, uint8_t index){
    uint8_t minDist1, minDist2, index1, index2;
    findClosestTile(t->index1, &index1, &minDist1);
    findClosestTile(t->index2, &index2, &minDist2);
    closestDestTiles[index] = (minDist1 < minDist2) ? index1 : index2;
}

void findRoute(uint8_t target){
    uint8_t i = (mapTiles[target].distance - 1), route[i + 1], currentTile = target;
    while(currentTile != start){
        route[i] = currentTile;
        currentTile = mapTiles[currentTile].prev;
        i--;
    }
    // print for debugging
    uint8_t x, y;
    conv1Dto2D(start, &x, &y);
    printf("(%d,%d) [Start] -> ", x, y);
    for (int j = 0; j < (mapTiles[target].distance - 1); ++j) {
        conv1Dto2D(route[j], &x, &y);
        printf("(%d,%d) -> ", x, y);
    }
    conv1Dto2D(route[mapTiles[target].distance - 1], &x, &y);
    printf("(%d,%d) [Target]\n", x, y);

    //
}

void printClosestTiles(){
    uint8_t tileIndex = closestDestTiles[0], x, y;
    conv1Dto2D(tileIndex, &x , &y);
    printf("Closest Index to Table %d is: (%d,%d) with a distance of %d\n",\
        destinations[0], x, y, mapTiles[tileIndex].distance);
    findRoute(tileIndex);
    tileIndex = closestDestTiles[1];
    conv1Dto2D(tileIndex, &x , &y);
    printf("Closest Index to Table %d is: (%d,%d) with a distance of %d\n",\
        destinations[1], x, y, mapTiles[tileIndex].distance);
    findRoute(tileIndex);
}

//TODO convert the path to node into actual driving instructions

/* Dijkstra Pathfinding End */

//TODO Driving & Use of sensors

int main() {
    convertMapStringToMatrix();
    findStartAndTablePosition();
    dijkstra();
    printSolutionMatrix();
    findClosestTableTile(&tables[destinations[0] - 1], 0);
    findClosestTableTile(&tables[destinations[1] - 1], 1);
    printClosestTiles();
    return 0;
}

