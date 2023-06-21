#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

#include "types.h"

uint8_t getStart();
tile * getMapTiles();
uint8_t getDestTile(uint8_t);

void initDijkstra();
void initMapTiles();
void initTablesArray();

void convertMapStringToMatrix();

void findStartAndTablePosition();
bool isTablePosition(char);
bool isStartPosition(char);
void fillTablePosition(uint8_t, uint8_t, uint8_t);

void dijkstra();
uint8_t minDistance();
void exploreSurroundings(uint8_t, uint8_t *);
bool leftExists(uint8_t);
bool rightExists(uint8_t);
bool aboveExists(uint8_t);
bool belowExists(uint8_t);

void findClosestTableTile(uint8_t);
void findClosestTile(uint8_t, uint8_t *, uint8_t *);

#endif
