#include "mapDisplay.h"
#include "utils.h"
#include "types.h"
#include "motion.h"
#include "nnxt.h"


/* Matrix conversion */

void convertMapStringToMatrix(char (*mapStringMatrix)[14]){
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
// TODO remove global var
uint8_t destinations[] = {3, 3};
// start index is stored as 1D index
// TODO remove global var
//uint8_t start;
// holds the tables positions at index [table name (either 1,2 or 3) - 1]
// TODO remove global var
table tables[3];

void findStartAndTablePosition(char (*mapStringMatrix)[14], uint8_t * start){

    initTablesArray();

    char currentChar;
    uint8_t tableIndex;
    for (int8_t i = 1; i < 13; i++){
        for (int8_t j = 1; j < 13; j++) {
            currentChar = mapStringMatrix[i][j];
            if (isStartPosition(currentChar)) {
                *start = conv2Dto1D(i,j);
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
void dijkstra(char (*mapStringMatrix)[14], const uint8_t start){
    initMapTiles();

    mapTiles[start].distance = 0;

    for (uint8_t i = 0; i < 196 - 1; ++i){
        uint8_t x, y;
        uint8_t minIndex = minDistance();
        uint8_t adjacent[4] = {UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX};

        mapTiles[minIndex].visited = true;
        exploreSurroundings(minIndex, adjacent);

        for(uint8_t j = 0; j < 4; ++j){
            if(adjacent[j] != UINT8_MAX){
                conv1Dto2D(adjacent[j], &x, &y);

                /*
                if (mapStringMatrix[x][y] == ' '
                    && mapTiles[minIndex].distance != UINT8_MAX
                    && !mapTiles[j].visited
                    && (mapTiles[minIndex].distance + 1) < mapTiles[adjacent[j]].distance){
                    mapTiles[adjacent[j]].distance = mapTiles[minIndex].distance + 1;
                    mapTiles[adjacent[j]].prev = minIndex;
                }
                */

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

void findClosestTile(uint8_t tableIndex, uint8_t* lowestTableIndex, uint8_t* lowestDistance){
    uint8_t currentMinDistance = UINT8_MAX;
    uint8_t x, y;

    conv1Dto2D(tableIndex, &x, &y);

    for (uint16_t row = (x - 1); row <= (x + 1); ++row) {
        for (uint16_t col = (y - 1); col <= (y + 1); ++col) {
            /*
            if(!(x < 0 || y < 0 || x >= 14 || y >= 14) && mapTiles[conv2Dto1D(row, col)].distance < currentMinDistance){
                index = conv2Dto1D(row, col);
                currentMinDistance = mapTiles[index].distance;
                *lowestTableIndex = index;
            }
            */

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
void findClosestTableTile(table* t, uint8_t index){
    uint8_t minDist1, minDist2, index1, index2;

    findClosestTile(t->index1, &index1, &minDist1);
    findClosestTile(t->index2, &index2, &minDist2);

    closestDestTiles[index] = (minDist1 < minDist2) ? index1 : index2;
}

void findRoute(uint8_t target, char (*mapStringMatrix)[14], direction * roboDirection, const uint8_t start){
    // TODO finish stuff here
    // create Route
    uint8_t dist = mapTiles[target].distance;
    uint8_t route[dist];
    uint8_t arrRouteIndex = dist - 1;
    //uint8_t length = dist;
    uint8_t currentTile = target;

    uint8_t currentIndex = start;
    uint8_t forwardCount = 0;


    while(currentTile != start){
        route[arrRouteIndex] = currentTile;
        currentTile = mapTiles[currentTile].prev;
        --arrRouteIndex;
    }

    printRouteToMap(route, dist, 0, 1, mapStringMatrix, *roboDirection);
    makeSound();

    // drive to target
    //uint8_t currentIndex = start
    //uint8_t forwardCount = 0;

    for (uint8_t i = 0; i <= (dist - 1); ++i) {
        direction turnsTo = headsTo(currentIndex, route[i]);
        int8_t turn = turnDegrees(turnsTo, roboDirection);

        switch (turn) {
            case 0:
                forwardCount++;
                break;
            case 1:
                if(forwardCount)
                    driveTile(forwardCount);
                forwardCount = 1;
                turnRight();
                //setRoboDir(turnsTo);
                *roboDirection = turnsTo;
                printRouteToMap(route, dist, i, 1, mapStringMatrix, *roboDirection);
                break;
            case -1:
                if(forwardCount)
                    driveTile(forwardCount);
                forwardCount = 1;
                turnLeft();
                //setRoboDir(turnsTo);
                *roboDirection = turnsTo;
                printRouteToMap(route, dist, i, 1, mapStringMatrix, *roboDirection);
                break;
        }
        currentIndex = route[i];
    }
    if(forwardCount){
        driveTile(forwardCount);
        printRouteToMap(route, dist, dist, 1, mapStringMatrix, *roboDirection);
    }

    makeSound();
    turnAround();
    //setRoboDir(turnDirections(getRoboDir(), 2, true));
    *roboDirection = turnDirections(*roboDirection, 2, true);

    forwardCount = 0;

    // drive back
    uint8_t routeBack[dist + 1];
    routeBack[0] = start;
    for (uint8_t k = 0; k < dist + 1; k++) {
        routeBack[k+1] = route[k];
    }

    printRouteToMap(routeBack, dist + 1, 0, 0, mapStringMatrix, *roboDirection);

    for (uint8_t k = (dist - 1); k < INT8_MAX; --k) {
        direction turnsTo = headsTo(currentIndex, routeBack[k]);
        int8_t turn = turnDegrees(turnsTo, roboDirection);
        switch (turn) {
            case 0:
                forwardCount++;
                break;
            case 1:
                if(forwardCount)
                    driveTile(forwardCount);
                forwardCount = 1;
                turnRight();
                //setRoboDir(turnsTo);
                *roboDirection = turnsTo;
                printRouteToMap(routeBack, dist + 1, k, 0, mapStringMatrix, *roboDirection);
                break;
            case -1:
                if(forwardCount)
                    driveTile(forwardCount);
                forwardCount = 1;
                turnLeft();
                //setRoboDir(turnsTo);
                *roboDirection = turnsTo;
                printRouteToMap(routeBack, dist + 1, k, 0, mapStringMatrix, *roboDirection);
                break;
        }
        currentIndex = routeBack[k];
    }
    // turn the robot so it's facing downwards
    switch (turnDegrees(S, roboDirection)) {
        case 0:
            forwardCount++;
            break;
        case 1:
            if(forwardCount)
                driveTile(forwardCount);
            turnRight();
            //setRoboDir(S);
            *roboDirection = S;
            break;
        case -1:
            if(forwardCount)
                driveTile(forwardCount);
            turnLeft();
            //setRoboDir(S);
            *roboDirection = S;
            break;
        case 2:
            if(forwardCount)
                driveTile(forwardCount);
            turnAround();
            //setRoboDir(S);
            *roboDirection = S;
            break;
    }
}

/* Dijkstra Pathfinding End */

int main(){
    char mapStringMatrix[14][14];
    direction roboDirection = S;
    uint8_t start;

    initMotorPorts();
    //Delay(1000);
    convertMapStringToMatrix(mapStringMatrix);
    findStartAndTablePosition(mapStringMatrix, &start);
    printMap(mapStringMatrix);
    dijkstra(mapStringMatrix, start);
    findClosestTableTile(&tables[destinations[0] - 1], 0);
    findClosestTableTile(&tables[destinations[1] - 1], 1);
    findRoute(closestDestTiles[0], mapStringMatrix, &roboDirection, start);
    findRoute(closestDestTiles[1], mapStringMatrix, &roboDirection, start);
    makeSound();
    return 0;
}
