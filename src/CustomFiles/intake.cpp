#include "main.h"

void setIntake() {

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){

        if(cataDown){
            intake.move_velocity(600);
        }
        else {
            controller.rumble(".");
        }
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            intake.move_velocity(-300);
    }
    else {
            intake = 0;
    }
}
