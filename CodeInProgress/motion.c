#include "motion.h"
#include "types.h"
#include "nnxt.h"


#define RIGHT_MOTOR Port_A
#define LEFT_MOTOR Port_C

#define CIRCUMFERENCE 8

void initMotorPorts(){
    MotorPortInit(LEFT_MOTOR);
    MotorPortInit(RIGHT_MOTOR);
}

void driveTile(uint8_t tiles){
    // distance which should be driven in
    int16_t distance = 25 * tiles;

    uint32_t deg, prev_deg;

    // only works for Port_A !!!
    Motor_Tacho_GetCounter(RIGHT_MOTOR, &prev_deg);

    while(distance > 3) {
        Motor_Drive(LEFT_MOTOR, Motor_dir_forward, 50);
        Motor_Drive(RIGHT_MOTOR, Motor_dir_forward, 60);
        Delay(200);
        Motor_Tacho_GetCounter(RIGHT_MOTOR, &deg);
        distance -= (((deg-prev_deg)/360) * CIRCUMFERENCE);
        prev_deg = deg;
    }

    Motor_Stop(LEFT_MOTOR, Motor_stop_float);
    Motor_Stop(RIGHT_MOTOR, Motor_stop_float);
}

uint32_t getAbsDiff(uint32_t a, uint32_t b) {
    return ((a > b) ? (a - b): (b - a));
}

void turn(uint8_t dir) {

    int16_t distanceL, distanceR;
    distanceL = distanceR = (2.5 * 3.14) * 1000;
    uint32_t prev_degL, prev_degR, degL, degR;

    Motor_Tacho_GetCounter(RIGHT_MOTOR, &prev_degR);
    Motor_Tacho_GetCounter(LEFT_MOTOR, &prev_degL);

    Motor_Drive(LEFT_MOTOR, ((dir) ? Motor_dir_backward: Motor_dir_forward), 30);
    Motor_Drive(RIGHT_MOTOR, ((dir) ? Motor_dir_forward: Motor_dir_backward), 30);
    while (distanceL > 0 || distanceR > 0) {
        if (distanceL <= 0) {
            Motor_Stop(LEFT_MOTOR, MOTOR_stop_break);
        } else {
            Motor_Tacho_GetCounter(LEFT_MOTOR, &degL);
            distanceL -= ((getAbsDiff(degL, prev_degL)/360) * CIRCUMFERENCE * 1000);
            prev_degL = degL;
        }
        if (distanceR <= 0) {
            Motor_Stop(RIGHT_MOTOR, MOTOR_stop_break);
        } else {
            Motor_Tacho_GetCounter(RIGHT_MOTOR, &degR);
            distanceR -= ((getAbsDiff(degR, prev_degR)/360) * CIRCUMFERENCE * 1000);
            prev_degR = degR;
        }
        Delay(150);
    }
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