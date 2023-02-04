#include "main.h"
#include "autoSelect/selection.h"

void initialize() {
	selector::init();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {

	/*frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	middleRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	middleLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	backRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	*/
	rightSide();
}

void opcontrol() {

	cataCheckStart();

	while (true) {

		setBrakes();
		setDriveMotors();
		setIntake();
		setCatapult();
		cataCheckLaunch();
		shootStrings();

		pros::delay(10);

	}
}
