#include "utils.h"
#include "types.h"
#include "nnxt.h"


direction roboDirection = S;


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
    //char x[35];
    //sprintf("in findRoute target: %d", x, target);
    //printText(1, x);

    // create Route
    uint8_t i = (mapTiles[target].distance - 1), route[i + 1], currentTile = target, dist = mapTiles[target].distance;
    while(currentTile != start){
        route[i] = currentTile;
        currentTile = mapTiles[currentTile].prev;
        i--;
    }
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
                    //printf("driveTile(%d);\n", forwardCount);
                forwardCount = 1;
                turnRight();
                //printf(("turnRight();\n"));
                setRoboDir(to);
                break;
            case -1:
                if(forwardCount)
                    driveTile(forwardCount);
                    //printf("driveTile(%d);\n", forwardCount);
                forwardCount = 1;
                turnLeft();
                //printf(("turnLeft();\n"));
                setRoboDir(to);
                break;
        }
        currentIndex = route[j];
    }
    if(forwardCount){
        driveTile(forwardCount);
        //printf("driveTile(%d);\n", forwardCount);
    }

    makeSound();

    turnAround();
    //printf("\tturnAround();\n");
    setRoboDir(turnDirections(getRoboDir(), 2, true));
    forwardCount = 0;

    // drive back
    uint8_t routeBack[dist + 1];
    routeBack[0] = start;
    for (uint8_t k = 0; k < dist + 1; k++) {
        routeBack[k+1] = route[k];
    }

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
                    //printf("driveTile(%d);\n", forwardCount);
                forwardCount = 1;
                turnRight();
                //printf(("turnRight();\n"));
                setRoboDir(to);
                break;
            case -1:
                if(forwardCount)
                    driveTile(forwardCount);
                    //printf("driveTile(%d);\n", forwardCount);
                forwardCount = 1;
                turnLeft();
                //printf(("turnLeft();\n"));
                setRoboDir(to);
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
                //printf("driveTile(%d);\n", forwardCount);
            turnRight();
            //printf(("turnRight();\n"));
            setRoboDir(S);
            break;
        case -1:
            if(forwardCount)
                driveTile(forwardCount);
                //printf("driveTile(%d);\n", forwardCount);
            turnLeft();
            //printf(("turnLeft();\n"));
            setRoboDir(S);
            break;
        case 2:
            if(forwardCount)
                driveTile(forwardCount);
                //printf("driveTile(%d);\n", forwardCount);
            turnAround();
            //printf(("turnAround();\n"));
            setRoboDir(S);
            break;
    }
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

/* Dijkstra Pathfinding End */


void driveTest(uint8_t tiles){
    // distance which should be driven in
    char msg[20];
    char msg1[20];
    char msg2[20];
    char msg3[20];

    uint32_t prev_DegA = 0;
    uint32_t degA = 0;
    uint32_t prev_DegB = 0;
    uint32_t degB = 0;


    Motor_Tacho_GetCounter(Port_A, &prev_DegA);
    Motor_Tacho_GetCounter(Port_C, &prev_DegB);

    Motor_Drive(Port_A, Motor_dir_forward, 50);
    Motor_Drive(Port_C, Motor_dir_forward, 50);

    Delay(5000);

    Motor_Tacho_GetCounter(Port_A, &degA);
    Motor_Tacho_GetCounter(Port_C, &degB);

    Motor_Stop(Port_A, Motor_stop_break);
    Motor_Stop(Port_C, Motor_stop_break);


    sprintf(msg, "%d", (int)prev_DegA);
    sprintf(msg1, "%d", (int)prev_DegB);
    sprintf(msg2, "%d", (int)degA);
    sprintf(msg3, "%d", (int)degB);
    printText(0, msg);
    printText(1, msg1);
    printText(2, msg2);
    printText(3, msg3);
}


void SensorTest(uint8_t tiles){
    // distance which should be driven in
    char msg[20];

    uint32_t degA = 0;


    while(1)
    {
        Motor_Tacho_GetCounter(Port_A, &degA);
        sprintf(msg, "%d", (int)degA);
        printText(0, msg);
        Delay(100);
    }
}

int main(){
    initMotorPorts();
    Delay(1000);
    initMotorPorts();
    convertMapStringToMatrix();
    findStartAndTablePosition();
    dijkstra();
    //printSolutionMatrix();
    findClosestTableTile(&tables[destinations[0] - 1], 0);
    findClosestTableTile(&tables[destinations[1] - 1], 1);
    //printClosestTiles();
    findRoute(closestDestTiles[0]);
    findRoute(closestDestTiles[1]);

    makeSound();

    return 0;
}
