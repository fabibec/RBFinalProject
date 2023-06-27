#include "motion.h"


#define RIGHT_MOTOR Port_A
#define LEFT_MOTOR Port_C

//#define CIRCUMFERENCE 13.28
#define CIRCUMFERENCE 13.5
//#define CIRCUMFERENCE 26.56

void initMotorPorts(){
    MotorPortInit(LEFT_MOTOR);
    MotorPortInit(RIGHT_MOTOR);
    OnBoardPeriph_Beep_Init();
}

void driveTile(uint8_t tiles){
    /*int32_t distance = 25 * tiles * 1000;

    uint32_t deg, prev_deg;

    // only works for Port_A !!!
    Motor_Tacho_GetCounter(RIGHT_MOTOR, &prev_deg);

    Motor_Drive(LEFT_MOTOR, Motor_dir_forward, 51);
    Motor_Drive(RIGHT_MOTOR, Motor_dir_forward, 50);
    while(distance > 2000) {
        Delay(200);
        Motor_Tacho_GetCounter(RIGHT_MOTOR, &deg);


        distance -= ((getAbsDiff(deg, prev_deg)*2/360.0) * CIRCUMFERENCE * 1000);
        prev_deg = deg;
    }

    Motor_Stop(LEFT_MOTOR, Motor_stop_float);
    Motor_Stop(RIGHT_MOTOR, Motor_stop_float);*/

    char msg[20];
    char msg1[20];
    uint8_t temp = 0;

    int32_t distanceL, distanceR;
    distanceL = distanceR = 25 * tiles * 1000;

    uint32_t degL, degR, prevDegL, prevDegR;

    uint8_t motorL, motorR, diffL, diffR, offSet;
    motorL = 50;
    motorR = 50;
    offSet = 5;

    int32_t buffer = 2 * 1000;


    Motor_Tacho_GetCounter(LEFT_MOTOR, &prevDegL);
    Motor_Tacho_GetCounter(RIGHT_MOTOR, &prevDegR);

    Motor_Drive(LEFT_MOTOR, Motor_dir_forward, motorL);
    Motor_Drive(RIGHT_MOTOR, Motor_dir_forward, motorR);

    while((distanceL > buffer) && (distanceR > buffer))
    {
        Motor_Drive(LEFT_MOTOR, Motor_dir_forward, motorL);
        Motor_Drive(RIGHT_MOTOR, Motor_dir_forward, motorR);

        Motor_Tacho_GetCounter(LEFT_MOTOR, &degL);
        Motor_Tacho_GetCounter(RIGHT_MOTOR, &degR);

        diffL = getAbsDiff(degL, prevDegL);
        diffR = getAbsDiff(degR, prevDegR);

        distanceL -= ((diffL * 2 / 360.0) * CIRCUMFERENCE * 1000);
        distanceR -= ((diffR * 2 / 360.0) * CIRCUMFERENCE * 1000);
        prevDegL = degL;
        prevDegR = degR;

        if(diffL != diffR){
            if((diffL + offSet) < diffR)
            {
                ++motorL;
            }
            else if(diffL > (diffR + offSet))
            {
                ++motorR;
            }
        }

        //temp = temp ^ 1;
        sprintf(msg, "%ld", distanceL);
        sprintf(msg1, "%ld", distanceR);
        printText(0, msg);
        printText(1, msg1);

        Delay(200);
    }

    Motor_Stop(LEFT_MOTOR, Motor_stop_float);
    Motor_Stop(RIGHT_MOTOR, Motor_stop_float);
}

uint32_t getAbsDiff(uint32_t a, uint32_t b) {
    return ((a > b) ? (a - b) : (b - a));
}

void turn(uint8_t dir) {
    int16_t distanceL, distanceR;
    distanceL = distanceR = (2.0 * 3.14) * 1000;
    uint32_t prev_degL, prev_degR, degL, degR;
    uint8_t motorL = 20;
    uint8_t motorR = 20;
    uint8_t diffL = 0;
    uint8_t diffR = 0;
    uint8_t offSet = 4;

    Motor_Tacho_GetCounter(RIGHT_MOTOR, &prev_degR);
    Motor_Tacho_GetCounter(LEFT_MOTOR, &prev_degL);

    Motor_Drive(LEFT_MOTOR, ((dir) ? Motor_dir_backward: Motor_dir_forward), motorL);
    Motor_Drive(RIGHT_MOTOR, ((dir) ? Motor_dir_forward: Motor_dir_backward), motorR);
    while ((distanceL > 0) || (distanceR > 0)) {
        if (distanceL <= 0) {
            Motor_Stop(LEFT_MOTOR, Motor_stop_break);
        } else {
            Motor_Drive(LEFT_MOTOR, ((dir) ? Motor_dir_backward: Motor_dir_forward), motorL);
            Motor_Tacho_GetCounter(LEFT_MOTOR, &degL);
            diffL = getAbsDiff(degL, prev_degL);
            distanceL -= ((diffL*2/360.0) * CIRCUMFERENCE * 1000);
            prev_degL = degL;
        }
        if (distanceR <= 0) {
            Motor_Stop(RIGHT_MOTOR, Motor_stop_break);
        } else {
            Motor_Tacho_GetCounter(RIGHT_MOTOR, &degR);
            Motor_Drive(RIGHT_MOTOR, ((dir) ? Motor_dir_forward: Motor_dir_backward), motorR);
            diffR = getAbsDiff(degR, prev_degR);
            distanceR -= ((diffR*2/360.0) * CIRCUMFERENCE * 1000);
            prev_degR = degR;
        }
        if(diffL != diffR){
            if((diffL + offSet) < diffR)
            {
                ++motorL;
            }
            else if(diffL > (diffR + offSet))
            {
                ++motorR;
            }
        }

        Delay(200);
    }

    Motor_Stop(RIGHT_MOTOR, Motor_stop_float);
    Motor_Stop(LEFT_MOTOR, Motor_stop_float);

    /*int16_t distanceL, distanceR;
    distanceL = distanceR = (2.0 * 3.14) * 1000;

    uint32_t degL, degR, prevDegL, prevDegR;

    uint8_t motorL, motorR;
    motorL = 21;
    motorR = 20;

    Motor_Tacho_GetCounter(LEFT_MOTOR, &prevDegL);
    Motor_Tacho_GetCounter(RIGHT_MOTOR, &prevDegR);

    Motor_Drive(LEFT_MOTOR, ((dir) ? Motor_dir_backward: Motor_dir_forward), motorL);
    Motor_Drive(RIGHT_MOTOR, ((dir) ? Motor_dir_forward: Motor_dir_backward), motorR);

    while(distanceL > 0 && distanceR > 0)
    {
        Motor_Tacho_GetCounter(LEFT_MOTOR, &degL);
        Motor_Tacho_GetCounter(RIGHT_MOTOR, &degR);

        distanceL -= ((getAbsDiff(degL, prevDegL) * 2 / 360.0) * CIRCUMFERENCE * 1000);
        distanceR -= ((getAbsDiff(degR, prevDegR) * 2 / 360.0) * CIRCUMFERENCE * 1000);
        prevDegL = degL;
        prevDegR = degR;

        Delay(150);
    }

    Motor_Stop(LEFT_MOTOR, Motor_stop_float);
    Motor_Stop(RIGHT_MOTOR, Motor_stop_float);*/
}

void turnLeft(){
    turn(1);
}

void turnRight() {
    turn(0);
}

void turnAround(){
    //turnLeft();
    //turnLeft();
    turnRight();
    turnRight();
}

void makeSound(){
    OnBoardPeriph_Beep(500);
    for (uint8_t i = 0; i < 3; i++) {
        OnBoardPeriph_BeepCMD(Beep_on);
        Delay(500);
        OnBoardPeriph_BeepCMD(Beep_off);
        Delay(500);
    }
}
