#ifndef hardwareUtils_H
#define hardwareUtils_H

#include <stdint.h>

typedef enum {
    LEFT,
    RIGHT
} direction;

void driveForward(int8_t);
void turn(direction, int8_t);
void turnLeft();
void turnRight();


void makeSound();

#endif
