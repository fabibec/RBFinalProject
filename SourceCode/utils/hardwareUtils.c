#include "nnxt.h"
#include <stdint>


void turn(direction dir, int8_t amount){
    for (; amount != 0; amount--) {
        (dir == LEFT) ? turnLeft(): turnRight(); 
    }
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
