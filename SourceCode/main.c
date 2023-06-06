#include <stdint.h>
#include <stdio.h>
// include "nnxt.h"

// Rechter Fahrmotor Anschluss Port_A
// Linker Fahrmotor Anschluss Port_C
#define MotorRight Port_A
#define MotorLeft Port_C

char mapStringMatrix[14][14];

typedef enum {
    LEFT,
    RIGHT
} direction;

typedef enum {
    FALSE = 0,
    TRUE
} bool;

typedef struct {
    uint8_t x;
    uint8_t y;
} coord; 

coord tablePositionArray[3][2] = {{{0 ,0}, {0, 0}}, {{0, 0}, {0, 0}}, {{0, 0}, {0, 0}}};
                                
coord startPosition = {0, 0};

void convertMapStringToMatrix();
void printStringMatrix();
void findTableAndStartPosition();
void printTableAndStartPosition();

bool checkAbove(int8_t x, int8_t y);
bool checkBellow(int8_t x, int8_t y);
bool checkLeft(int8_t x, int8_t y);
bool checkRight(int8_t x, int8_t y);

bool isStartPosition(char);
bool isTablePosition(char);
bool tableNotFoundYet(char);

void driveForward(int8_t);
void turn(direction, int8_t);
void turnLeft();
void turnRight();
void makeSound();


int main(){
    // OnBoardPeriph_Beep_Init();
    convertMapStringToMatrix();
    findTableAndStartPosition();
    printStringMatrix();
    printTableAndStartPosition();
  	return 0;
}

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


// Debug functions
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
/*
void turn(direction dir, int8_t amount){
    for (; amount != 0; amount--) {
        (dir == LEFT) ? turnLeft(): turnRight(); 
    }
}

void makeSound(){

}

void driveForward(int8_t numberOfSquares){}
*/
