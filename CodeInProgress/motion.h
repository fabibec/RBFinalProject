#ifndef MOTION_H
#define MOTION_H
#include "types.h"

direction roboDirection = S;

void driveTile();
void turnLeft();
void turnRight();
void turnAround();
void setRoboDir(direction d);

#endif 
