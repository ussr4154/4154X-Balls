#include "main.h"

#define CATA_TARGET_POSITION 500
//Driver Position 8250
//Auton Position 8490
#define CATA_LAUNCHED_POSITION 6800
bool cataDown = false;
bool killSwitch = false;

void setCatapult(){
    if(cataPot.get_angle() < CATA_TARGET_POSITION){
        cataDown = true;
    }
    if(cataDown == true && !controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
        catapult = 0;
    }
    if(cataDown == false && !controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
        catapult = 127;
    }
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
        catapult.move_voltage(12000);
        cataDown = false;
    }
}

void cataCheckLaunch(){
    if(cataPot.get_angle() > CATA_LAUNCHED_POSITION){
        cataDown = false;
    }
}

void cataCheckStart(){
    if(cataPot.get_angle() > CATA_TARGET_POSITION){
        cataDown = false;
    }
}

void returnCata(){
    cataDown = false;
    while(true){
    if(cataPot.get_angle() < CATA_TARGET_POSITION){
        cataDown = true;
    }
    if(!cataDown){
        catapult = 127;
    }
    else {
        catapult = 0;
        break;
    }
    }   
}

