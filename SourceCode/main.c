#include "mapDisplay.h"
#include "utils.h"
#include "types.h"
#include "motion.h"
#include "dijkstra.h"


void runRobo(uint8_t targetIndex){
    direction roboDirection = S;

    const uint8_t start = getStart();
    const tile * mapTiles = getMapTiles();
    const uint8_t target = getDestTile(targetIndex);

    const uint8_t dist = mapTiles[target].distance;
    uint8_t route[dist];
    uint8_t arrRouteIndex = dist - 1;
    uint8_t currentTile = target;

    uint8_t currentIndex = start;
    uint8_t forwardCount = 0;


    while(currentTile != start){
        route[arrRouteIndex] = currentTile;
        currentTile = mapTiles[currentTile].prev;
        --arrRouteIndex;
    }

    printRoute(route, dist);
    makeSound();

    for(uint8_t i = 0; i <= (dist - 1); ++i){
        const direction turnsTo = headsTo(currentIndex, route[i]);
        int8_t turn = turnDegrees(turnsTo, roboDirection);

        switch(turn){
            case 0:
                forwardCount++;
                break;
            case 1:
                if(forwardCount)
                    driveTile(forwardCount, false);
                forwardCount = 1;
                turnRight();
                roboDirection = turnsTo;
                updateRoute(route, dist, i, roboDirection, 1);
                break;
            case -1:
                if(forwardCount)
                    driveTile(forwardCount, false);
                forwardCount = 1;
                turnLeft();
                roboDirection = turnsTo;
                updateRoute(route, dist, i, roboDirection, 1);
                break;
        }
        currentIndex = route[i];
    }
    if(forwardCount){
        driveTile(forwardCount, true);
        updateRoute(route, dist, dist, roboDirection, 1);
    }

    makeSound();
    Delay(500);
    turnAround();

    roboDirection = turnDirections(roboDirection, 2, true);
    forwardCount = 0;

    // drive back
    uint8_t routeBack[dist + 1];
    routeBack[0] = start;
    for(uint8_t i = 0; i < dist + 1; i++){
        routeBack[i + 1] = route[i];
    }

    printRoute(routeBack + 1, dist);

    for(uint8_t i = (dist - 1); i < INT8_MAX; --i){
        direction turnsTo = headsTo(currentIndex, routeBack[i]);
        int8_t turn = turnDegrees(turnsTo, roboDirection);
        switch(turn){
            case 0:
                forwardCount++;
                break;
            case 1:
                if(forwardCount)
                    driveTile(forwardCount, false);
                forwardCount = 1;
                turnRight();
                roboDirection = turnsTo;
                updateRoute(routeBack + 1, dist, i, roboDirection, 0);
                break;
            case -1:
                if(forwardCount)
                    driveTile(forwardCount, false);
                forwardCount = 1;
                turnLeft();
                roboDirection = turnsTo;
                updateRoute(routeBack + 1, dist, i, roboDirection, 0);
                break;
        }
        currentIndex = routeBack[i];
    }

    // turn the robot so it's facing south again
    switch(turnDegrees(S, roboDirection)){
        case 0:
            forwardCount++;
            break;
        case 1:
            if(forwardCount)
                driveTile(forwardCount, false);
            turnRight();
            roboDirection = S;
            break;
        case -1:
            if(forwardCount)
                driveTile(forwardCount, false);
            turnLeft();
            roboDirection = S;
            break;
        case 2:
            if(forwardCount)
                driveTile(forwardCount, false);
            turnAround();
            roboDirection = S;
            break;
    }
    updateRoute(routeBack + 1, dist, 0, roboDirection, 0);
}
void runDijkstra(){
    convertMapStringToMatrix();
    findStartAndTablePosition();

    printMap((char (*)[14])getMapStringMatrix(), getDestTablesAtIndex(0), getDestTablesAtIndex(1));

    dijkstra();
    findClosestTableTile(0);
    findClosestTableTile(1);
}
void init(){
    initMotorPorts();
    initDijkstra();
}

void debugTest(){
    printText(0, "Turning left");
    turnLeft();
    printText(0, "Done !");
    Delay(200);

    printText(1, "Turning right");
    turnRight();
    printText(1, "Done !");
    Delay(200);

    printText(2, "Turning around");
    turnAround();
    printText(2, "Done !");
    Delay(200);

    printText(3, "Driving 2 Tiles with anfahren");
    driveTile(2, true);
    printText(3, "Done !");
    Delay(200);

    printText(4, "Driving 2 Tiles without anfahren");
    driveTile(2, false);
    printText(4, "Done !");
    Delay(200);
}

int main(){
    init();
    runDijkstra();
    runRobo(0);
    runRobo(1);
    makeSound();
    //debugTest();

    return 0;
}
