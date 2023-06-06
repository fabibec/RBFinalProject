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


void convertMapStringToMatrix();
void printStringMatrix();
void driveForward(int8_t);
void turn(direction, int8_t);
void turnLeft();
void turnRight();
void makeSound();


int main(){
    // OnBoardPeriph_Beep_Init();
    convertMapStringToMatrix();
    printStringMatrix();
  	return 0;
}

void convertMapStringToMatrix(){
    const char* mapString = "###############     S      ###   #####   ##    11      ##            ##   ####   2 ##      #   2 ##      #     ##   ###########   #        ##   #   33   ##   #        ##            ###############";

    for (uint8_t i = 0; i < 196; i++) {
        mapStringMatrix[(i/14)][(i%14)] = mapString[i];
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
