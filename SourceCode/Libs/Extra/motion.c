#include "motion.h"
#include "types.h"
#include "nnxt.h"


#define RIGHT_MOTOR Port_A
#define LEFT_MOTOR Port_C

#define CIRCUMFERENCE 13.28
//#define CIRCUMFERENCE 26.56

void initMotorPorts(){
    MotorPortInit(LEFT_MOTOR);
    MotorPortInit(RIGHT_MOTOR);
    OnBoardPeriph_Beep_Init();
}

void driveTile(uint8_t tiles){
    // distance which should be driven in
    char msg[20];
    char msg1[20];
    char msg2[20];
    char msg3[20];
    int32_t distance = 25 * tiles * 1000;

    uint32_t deg, prev_deg;

    // only works for Port_A !!!
    Motor_Tacho_GetCounter(RIGHT_MOTOR, &prev_deg);

    sprintf(msg, "%d", distance);

    Motor_Drive(LEFT_MOTOR, Motor_dir_forward, 51);
    Motor_Drive(RIGHT_MOTOR, Motor_dir_forward, 50);
    while(distance > 2000) {
        sprintf(msg, "%d", distance);
        printText(0, msg);

        Delay(200);
        Motor_Tacho_GetCounter(RIGHT_MOTOR, &deg);


        sprintf(msg1, "%d", (int)deg);
        sprintf(msg2, "%d", (int)prev_deg);
        printText(1, msg1);
        printText(2, msg2);

        distance -= ((getAbsDiff(deg, prev_deg)*2/360.0) * CIRCUMFERENCE * 1000);
        prev_deg = deg;
    }

    Motor_Stop(LEFT_MOTOR, Motor_stop_float);
    Motor_Stop(RIGHT_MOTOR, Motor_stop_float);
}

uint32_t getAbsDiff(uint32_t a, uint32_t b) {
    return ((a > b) ? (a - b): (b - a));
}

void turn(uint8_t dir) {
    char msg[20];
    char msg1[20];


    int16_t distanceL, distanceR;
    distanceL = distanceR = (2.0 * 3.14) * 1000;
    uint32_t prev_degL, prev_degR, degL, degR;

    Motor_Tacho_GetCounter(RIGHT_MOTOR, &prev_degR);
    Motor_Tacho_GetCounter(LEFT_MOTOR, &prev_degL);

    Motor_Drive(LEFT_MOTOR, ((dir) ? Motor_dir_backward: Motor_dir_forward), 20);
    Motor_Drive(RIGHT_MOTOR, ((dir) ? Motor_dir_forward: Motor_dir_backward), 20);
    while (distanceL > 0 || distanceR > 0) {
        sprintf(msg, "%d", (int)distanceL);
        sprintf(msg1, "%d", (int)distanceR);
        printText(1, msg);
        printText(2, msg1);

        if (distanceL <= 0) {
            Motor_Stop(LEFT_MOTOR, Motor_stop_break);
        } else {
            Motor_Tacho_GetCounter(LEFT_MOTOR, &degL);
            distanceL -= ((getAbsDiff(degL, prev_degL)*2/360.0) * CIRCUMFERENCE * 1000);
            prev_degL = degL;
        }
        if (distanceR <= 0) {
            Motor_Stop(RIGHT_MOTOR, Motor_stop_break);
        } else {
            Motor_Tacho_GetCounter(RIGHT_MOTOR, &degR);
            distanceR -= ((getAbsDiff(degR, prev_degR)*2/360.0) * CIRCUMFERENCE * 1000);
            prev_degR = degR;
        }
        Delay(150);
    }

    Motor_Stop(RIGHT_MOTOR, Motor_stop_float);
    Motor_Stop(LEFT_MOTOR, Motor_stop_float);
}

void turnLeft(){
    turn(1);
}

void turnRight() {
    turn(0);
}

void turnAround(){
    turnLeft();
    turnLeft();
}

void makeSound(){
    OnBoardPeriph_Beep(100);
    for (uint8_t i = 0; i < 3; i++) {
        OnBoardPeriph_BeepCMD(Beep_on);
        Delay(500);
        OnBoardPeriph_BeepCMD(Beep_off);
        Delay(500);
    }
}
