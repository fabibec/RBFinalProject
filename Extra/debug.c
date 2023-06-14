#include "debug.h"
#include "utils.h"
#include "stdio.h"

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

