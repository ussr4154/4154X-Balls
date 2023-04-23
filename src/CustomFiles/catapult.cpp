#include "main.h"

#define CATA_TARGET_POSITION 1100
//Driver Position 450
//Auton Position 350
#define CATA_LAUNCHED_POSITION 7500
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

