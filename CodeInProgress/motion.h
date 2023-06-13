#ifndef MOTION_H
#define MOTION_H


void initMotorPorts();
void driveTile();
void turn(uint8_t);
void turnLeft();
void turnRight();
void turnAround();
void makeBeep();
uint32_t getAbsDiff(uint32_t, uint32_t);

#endif 
