#include "mapDisplay.h"
#include "utils.h"
#include "types.h"
#include "motion.h"
#include "nnxt.h"

direction roboDirection = S;


/* Matrix conversion */
char mapStringMatrix[14][14];

void convertMapStringToMatrix(){
    const char* mapString = "\
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
##############";

    //const char* mapString = "###############     S      ###   #####   ##    11      ##            ##   ####   2 ##      #   2 ##      #     ##   ###########   #        ##   #   33   ##   #        ##            ###############";

    for (uint8_t i = 0; i < 196; i++) {
        mapStringMatrix[(i/14)][(i%14)] = mapString[i];
    }
}
/* Matrix conversion End*/


/* Tracking start and possible end positions */
uint8_t destinations[] = {3, 3};
// start index is stored as 1D index
uint8_t start;
// holds the tables positions at index [table name (either 1,2 or 3) - 1]
table tables[3];

void findStartAndTablePosition(){

    initTablesArray();

    char currentChar;
    uint8_t tableIndex;
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
/* Tracking start and possible end positions - end */


/* Dijkstra Pathfinding */
tile mapTiles[196];
uint8_t closestDestTiles[2];
void initMapTiles(){
    for(uint8_t i = 0; i < 196; ++i){
        mapTiles[i].visited = false;
        mapTiles[i].distance = UINT8_MAX;
        mapTiles[i].prev = i;
    }
}
void dijkstra(){
    initMapTiles();

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
    // create Route
    uint8_t i = (mapTiles[target].distance - 1), route[i + 1], size = i + 1, currentTile = target, dist = mapTiles[target].distance;
    while(currentTile != start){
        route[i] = currentTile;
        currentTile = mapTiles[currentTile].prev;
        i--;
    }
    printRouteToMap(&route, size, 0, 1);
    makeSound();

    // drive to target
    uint8_t currentIndex = start, forwardCount = 0;
    for (uint8_t j = 0; j <= (dist - 1); ++j) {
        direction to = headsTo(currentIndex, route[j]);
        int8_t turn = turnDegrees(to);
        switch (turn) {
            case 0:
                forwardCount++;
                break;
            case 1:
                if(forwardCount)
                    driveTile(forwardCount);
                forwardCount = 1;
                turnRight();
                setRoboDir(to);
                printRouteToMap(&route, size, j, 1);
                break;
            case -1:
                if(forwardCount)
                    driveTile(forwardCount);
                forwardCount = 1;
                turnLeft();
                setRoboDir(to);
                printRouteToMap(&route, size, j, 1);
                break;
        }
        currentIndex = route[j];
    }
    if(forwardCount){
        driveTile(forwardCount);
        printRouteToMap(&route, size, size, 1);
    }

    makeSound();
    turnAround();
    setRoboDir(turnDirections(getRoboDir(), 2, true));
    forwardCount = 0;

    // drive back
    uint8_t routeBack[dist + 1];
    routeBack[0] = start;
    for (uint8_t k = 0; k < dist + 1; k++) {
        routeBack[k+1] = route[k];
    }

    printRouteToMap(&routeBack, dist + 1, 0, 0);

    for (uint8_t k = (dist - 1); k < INT8_MAX; --k) {
        direction to = headsTo(currentIndex, routeBack[k]);
        int8_t turn = turnDegrees(to);
        switch (turn) {
            case 0:
                forwardCount++;
                break;
            case 1:
                if(forwardCount)
                    driveTile(forwardCount);
                forwardCount = 1;
                turnRight();
                setRoboDir(to);
                printRouteToMap(&routeBack, dist + 1, k, 0);
                break;
            case -1:
                if(forwardCount)
                    driveTile(forwardCount);
                forwardCount = 1;
                turnLeft();
                setRoboDir(to);
                printRouteToMap(&routeBack, dist + 1, k, 0);
                break;
        }
        currentIndex = routeBack[k];
    }
    // turn the robot so it's facing downwards
    switch (turnDegrees(S)) {
        case 0:
            forwardCount++;
            break;
        case 1:
            if(forwardCount)
                driveTile(forwardCount);
            turnRight();
            setRoboDir(S);
            break;
        case -1:
            if(forwardCount)
                driveTile(forwardCount);
            turnLeft();
            setRoboDir(S);
            break;
        case 2:
            if(forwardCount)
                driveTile(forwardCount);
            turnAround();
            setRoboDir(S);
            break;
    }
}

/* Dijkstra Pathfinding End */

int main(){
    initMotorPorts();
    //Delay(1000);
    convertMapStringToMatrix();
    findStartAndTablePosition();
    printMap();
    dijkstra();
    findClosestTableTile(&tables[destinations[0] - 1], 0);
    findClosestTableTile(&tables[destinations[1] - 1], 1);
    findRoute(closestDestTiles[0]);
    findRoute(closestDestTiles[1]);
    makeSound();
    return 0;
}
