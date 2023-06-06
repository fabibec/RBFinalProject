#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
// include "nnxt.h"
// include "utils/hardwareUtils.h"
#include "utils/matrixUtils.h"

// Rechter Fahrmotor Anschluss Port_A
// Linker Fahrmotor Anschluss Port_C
#define MotorRight Port_A
#define MotorLeft Port_C



int main(){
    // OnBoardPeriph_Beep_Init();
    convertMapStringToMatrix();
    findTableAndStartPosition();

    // Debug Functions
    printStringMatrix();
    printTableAndStartPosition();
  	return 0;
}

