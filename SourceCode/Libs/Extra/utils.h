#ifndef UTILS_H
#define UTILS_H

#include "types.h"


/* use 1D as 2D and vise versa*/
uint8_t conv2Dto1D(const uint8_t, const uint8_t);
void conv1Dto2D(const uint8_t, uint8_t *, uint8_t *);


/* Driving */
direction headsTo(const uint8_t, const uint8_t);
int8_t turnDegrees(const direction, const direction);
direction turnDirections(const direction, const int8_t, const bool);


/* Debug */
void clearLine(const uint8_t);
void printText(const uint8_t, char *);


void playFanfare();
#endif //UTILS_H
