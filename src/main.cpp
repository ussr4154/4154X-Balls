#include "main.h"
#include "autoSelect/selection.h"

void initialize() {
	selector::init();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {

	frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	middleRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	middleLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	backRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	

	/*if(selector::auton == 1){
		leftSide();
	}
	if(selector::auton == -1){
		leftSide();
	}
	if(selector::auton == 2){
		rightSide();
	}
	if(selector::auton == -2){
		rightSide();
	}
	if(selector::auton == 3){
		fullWinPoint();
	}
	if(selector::auton == -3){
		fullWinPoint();
	}
	if(selector::auton == 0){
		skills();
	}*/

	skills();
} 

void opcontrol() {

	cataCheckStart();
	bandRelease.set_value(true);

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
