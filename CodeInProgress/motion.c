#include "motion.h"
#include "types.h"

#define LEFT_MOTOR Port_B
#define RIGHT_MOTOR Port_A




void driveTile(){
    Motor_Drive(LEFT_MOTOR, Motor_dir_forward, 30);
    Motor_Drive(RIGHT_MOTOR, Motor_dir_forward, 30);
    Delay(1000); 
    Motor_Stop(LEFT_MOTOR, MOTOR_stop_float);
    Motor_Stop(RIGHT_MOTOR, MOTOR_stop_float);
    Delay(250);
}

void turnLeft(){
    Motor_Drive(LEFT_MOTOR, Motor_dir_backward, 30);
    Motor_Drive(RIGHT_MOTOR, Motor_dir_forward, 30);
    Delay(100);
    Motor_Stop(LEFT_MOTOR, MOTOR_stop_float);
    Motor_Stop(RIGHT_MOTOR, MOTOR_stop_float);
    roboDirection = (roboDirection + 1) % 4;
}

void turnRight(){
    Motor_Drive(LEFT_MOTOR, Motor_dir_forward, 30);
    Motor_Drive(RIGHT_MOTOR, Motor_dir_backward, 30);
    Delay(100);
    Motor_Stop(LEFT_MOTOR, MOTOR_stop_float);
    Motor_Stop(RIGHT_MOTOR, MOTOR_stop_float);
    roboDirection = (roboDirection - 1) % 4;
}

void turnAround(){
    turnLeft();
    turnLeft();
}
