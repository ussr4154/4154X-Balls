#include "main.h"

void shootStrings(){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
        expansion.set_value(true);
    }
}