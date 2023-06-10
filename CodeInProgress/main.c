#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/* Matrix conversion */
char mapStringMatrix[14][14];

void convertMapStringToMatrix(){
    const char* mapString = "###############     S      ###   #####   ##    11      ##            ##   ####   2 ##      #   2 ##      #     ##   ###########   #        ##   #   33   ##   #        ##            ###############";

    for (uint8_t i = 0; i < 196; i++) {
        mapStringMatrix[(i/14)][(i%14)] = mapString[i];
    }
}
/* Matrix conversion End*/

/* utils - use 1D as 2D and vise versa*/
uint8_t conv2Dto1D(uint8_t row, uint8_t col){
    return row * 14 + col;
}

void conv1Dto2D(uint8_t index, uint8_t* row, uint8_t* col){
    *row = index / 14;
    *col = index % 14;
}
/* utils - end */

/* Tracking start and possible end positions */
uint8_t destinations[] = {2, 3};
// start index is stored as 1D index
uint8_t start;
typedef struct {
    // holds table position as 2 1D Indexes
    uint8_t index1;
    uint8_t index2;
} table;
// holds the tables positions at index [table name (either 1,2 or 3) - 1]
table tables[3];

bool isTablePosition(char c){
    return (c == '1' || c == '2' || c == '3');
}

void findStartAndTablePosition(){
    // init tables array
    for (int i = 0; i < 3; ++i) {
        tables[i].index1 = UINT8_MAX;
        tables[i].index2 = UINT8_MAX;
    }

    char currentChar;
    uint8_t x;
    for (int8_t i = 1; i < 13; i++){
        for (int8_t j = 1; j < 13; j++) {
            currentChar = mapStringMatrix[i][j];
            if (currentChar == 'S') {
                start = conv2Dto1D(i,j);
            } else if (isTablePosition(currentChar)){
                x = (currentChar - '1');
                if(tables[x].index1 == UINT8_MAX){
                    tables[x].index1 = conv2Dto1D(i, j);
                } else {
                    tables[x].index2 = conv2Dto1D(i, j);
                }
            }
        }
    }
}

void printStartAndTablePosition(){
    uint8_t x, y;
    conv1Dto2D(start, &x, &y);
    printf("Start: (%d,%d)\n\n", x, y);
    for (int i = 0; i < 3; ++i) {
        printf("Table %d:\n", i + 1);
        conv1Dto2D(tables[i].index1, &x, &y);
        printf("(%d,%d) ", x, y);
        conv1Dto2D(tables[i].index2, &x, &y);
        printf("(%d,%d)\n\n", x, y);
    }
}
/* Tracking start and possible end positions - end */

/* Dijkstra Pathfinding */
typedef struct{
    bool visited;
    uint16_t distance; // distance to start
    uint8_t prev; //address of previous
} tile;
tile mapTiles[196];

// prints the solution as a list
void printSolution(){
    uint8_t x, y, x2, y2;
    uint8_t distance;
    printf("Vertex\t\tDistance from Source\t\tFrom\n");
    for (uint8_t i = 0; i < 196; i++) {
        distance = mapTiles[i].distance;
        if (distance < UINT8_MAX) {
            conv1Dto2D(mapTiles[i].prev, &x, &y);
            conv1Dto2D(i, &x2, &y2);
            printf("(%d,%d)\t\t\t\t%d\t\t(%d,%d)\n", x2, y2, distance, x, y);
        }
    }
}

// prints the solution inside the matrix
void printSolutionMatrix(){
    char currentChar;
    for (uint8_t x = 0; x < 14; ++x) {
        for (uint8_t y = 0; y < 14; ++y) {
            currentChar = mapStringMatrix[x][y];
            if(currentChar != ' '){
                for (uint8_t  v = 0; v < 4; ++v) {
                    putchar(currentChar);
                }
            } else {
                printf("|%02d|" ,mapTiles[conv2Dto1D(x,y)].distance);
            }
        }
        printf("\n");
    }
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
        if(u >= 14){
            adjacent[0] = u - 14;
        }
        if(u <= 196 - 1 - 14){
            adjacent[1] = u + 14;
        }
        if(u != 0 || u % 14 != 0){
            adjacent[2] = u - 1;
        }
        if(u != 196 - 1 || u % 14 != 13){
            adjacent[3] = u + 1;
        }
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

uint8_t findClosestTableTile(table* t){
    uint8_t minDist1, minDist2, index1, index2;
    findClosestTile(t->index1, &index1, &minDist1);
    findClosestTile(t->index2, &index2, &minDist2);
    return (minDist1 < minDist2) ? index1 : index2;
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
}

void printClosestTiles(){
    uint8_t tileIndex = findClosestTableTile(&tables[destinations[0] - 1]), x, y;
    conv1Dto2D(tileIndex, &x , &y);
    printf("Closest Index to Table %d is: (%d,%d) with a distance of %d\n",\
        destinations[0], x, y, mapTiles[tileIndex].distance);
    findRoute(tileIndex);
    tileIndex = findClosestTableTile(&tables[destinations[1] - 1]);
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
    printClosestTiles();
    return 0;
}

