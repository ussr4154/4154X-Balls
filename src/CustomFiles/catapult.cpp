#include "main.h"

bool cataDown = false;

void setCatapult(){
    if(cataLimit.get_value()){
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

void returnCata(){
    cataDown = false;
    while(true){
    if(cataLimit.get_value()){
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