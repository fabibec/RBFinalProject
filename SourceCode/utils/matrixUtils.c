#include "matrixUtils.h"
#include <stdio.h>

void convertMapStringToMatrix(){
    const char* mapString = "###############     S      ###   #####   ##    11      ##            ##   ####   2 ##      #   2 ##      #     ##   ###########   #        ##   #   33   ##   #        ##            ###############";

    for (uint8_t i = 0; i < 196; i++) {
        mapStringMatrix[(i/14)][(i%14)] = mapString[i];
    }

}


void findTableAndStartPosition(){
    for (int8_t i = 1; i < 13; i++){
        for (int8_t j = 1; j < 13; j++) {

            char currentChar = mapStringMatrix[i][j]; 
            if (isStartPosition(currentChar)){
                startPosition.y = i;
                startPosition.x = j;
                    
            } else if (isTablePosition(currentChar) && tableNotFoundYet(currentChar)) {
                uint8_t index = (tablePositionArray[(uint8_t)currentChar - 49][0].x == 0) ? 0: 1; 
                tablePositionArray[(uint8_t)currentChar - 49][index].y = i;
                tablePositionArray[(uint8_t)currentChar - 49][index].x = j;
            }
        } 
    }
}

bool isStartPosition(char c){
    return (c == 'S');
}
bool isTablePosition(char c){
    return (c >= 49 && c <= 51);
}
bool tableNotFoundYet(char c) {
   return (tablePositionArray[(uint8_t)c - 49][0].x == 0 || tablePositionArray[(uint8_t)c - 49][1].x == 0); 
}




bool checkField(int8_t x, int8_t y) {
    return (mapStringMatrix[y][x] == ' ');
}

bool checkAbove(int8_t x, int8_t y){
    return checkField(x, y - 1);
}
bool checkBelow(int8_t x, int8_t y){
    return checkField(x, y + 1);
}
bool checkLeft(int8_t x, int8_t y){
    return checkField(x - 1, y);
}
bool checkRight(int8_t x, int8_t y){
    return checkField(x + 1, y);
}



// Debug function
void printTableAndStartPosition(){
    printf("\nStart Position: x=%d, y=%d\n", startPosition.x, startPosition.y);
    for (uint8_t i = 0; i < 3; i++){
        for (uint8_t j = 0; j < 2; j++) {
        printf("Table Position %d: x=%d, y=%d\n", (i+1), tablePositionArray[i][j].x, tablePositionArray[i][j].y);        
        }
    }
}

void printStringMatrix(){
    for (int i = 0; i< 14; i++) {
        for (int j = 0; j < 14; j++){
            printf("%c", mapStringMatrix[i][j]);
        }
        printf("\n");
    }
}
