#include "main.h"
#define CATA_AUTON_POSITION 440 //Normal 400

// Chassis constructor
Drive EZchassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {15, 17, 16}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{13, 11, 12}

  // IMU Port
  ,18

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.5

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  ,{1, 2}

  // Right Tracking Wheel Ports (negative port will reverse it!)
  ,{3, 4}
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,9
);

void goForward(int distance){

    double wheelCircumference = 10.2101761242;
    double ticksPerRevolution = 500.0;
    double constant = (wheelCircumference/ticksPerRevolution);

    int target = (distance/constant);

    middleLeft.tare_position();

    float kP = 0.1;
    float kD = 0.01;
    float prevError = 0.0;

  while(fabs(middleLeft.get_position() < target)){

    double error = distance - middleLeft.get_position();
    double derivative = error - prevError;
    prevError = error;

    int power = (error*kP) + (derivative*kD);

    frontLeft = power;
    frontRight = -power;
    middleLeft = power;
    middleRight = -power;
    backLeft = power;
    backRight = -power;

  }

  frontLeft = 0;
  frontRight = 0;
  middleLeft = 0;
  middleRight = 0;
  backLeft = 0;
  backRight = 0;

}

void defaultConstants() {
  EZchassis.set_slew_min_power(80, 80);
  EZchassis.set_slew_distance(7, 7);
  EZchassis.set_pid_constants(&EZchassis.headingPID, 10, 0, 20, 0);
  EZchassis.set_pid_constants(&EZchassis.forward_drivePID, 0.45, 0, 5, 0);
  EZchassis.set_pid_constants(&EZchassis.backward_drivePID, 0.45, 0, 5, 0);
  EZchassis.set_pid_constants(&EZchassis.turnPID, 0.02, 0.015, 0, 5);
  EZchassis.set_pid_constants(&EZchassis.swingPID, 7, 0, 45, 0);
}

void cataReturn(){
    cataDown = false;
    while(true){
    if(cataPot.get_angle() < CATA_AUTON_POSITION){
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

void cataReturnTimeout(){
    catapult = 127;
    pros::delay(1300);
    catapult = 0;
}
void killCata(){
  cataDown = true;
  catapult = 0;
}

void launchCata(){
  catapult = 127;
  pros::delay(800);
  cataDown = false;
  catapult = 0;
}

void launchAssistedCata(){
  catapult = 127;
  pros::delay(1000);
  cataDown = false;
  catapult = 0;
}

void spinRoller(int theta, bool rev = false){
  intake.tare_position();
  
  if(rev){
    while(fabs(intake.get_position()) < theta){
    intake = 127;
    }
  }
  else {
    while(fabs(intake.get_position()) < theta){
      intake = -127;
    }
  }

  intake = 0;
}

void clearEncoders(){
  frontLeft.tare_position();
  frontRight.tare_position();
  middleLeft.tare_position();
  middleRight.tare_position();
  backLeft.tare_position();
  backRight.tare_position();
}


void leftSide(){

  EZchassis.set_drive_pid(-5, 80, true);
  EZchassis.wait_drive();

  spinRoller(260);

  EZchassis.set_drive_pid(3, 127, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-10, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(6, 50, true);

  pros::delay(40);

  launchCata();

  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-45, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-3.5, 80, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-133, 60);

  cataReturn();

  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-20, 100, true);
  EZchassis.wait_drive();

  intake = 127;

  EZchassis.set_drive_pid(-28, 40, true);
  EZchassis.wait_drive();

  pros::delay(500);

  intake = -127;

  EZchassis.set_drive_pid(-14, 100, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-43, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-3, 60, true);
  EZchassis.wait_drive();

  intake = 0;

  launchCata();

  EZchassis.set_drive_pid(3, 100, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-133, 60);
  
  cataReturn();

  EZchassis.wait_drive();

  intake = 127;

  EZchassis.set_drive_pid(-65, 70, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-89, 60);
  EZchassis.wait_drive();

  intake = 0;

  EZchassis.set_drive_pid(-3.5, 50, true);
  EZchassis.wait_drive();

  spinRoller(260);




  



  /*EZchassis.set_drive_pid(33, 120, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(10, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(49, 120, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-43.5, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-11, 80, true);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(16, 50, true);

  pros::delay(250);

  launchCata();

  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-12, 80, true);

  cataReturnTimeout();

  EZchassis.wait_drive();

  killCata();

  EZchassis.set_turn_pid(-135, 60);
  EZchassis.wait_drive();

  cataReturn();

  intake = 127;

  EZchassis.set_drive_pid(-30, 60, true);
  EZchassis.wait_drive();
  */
  







  /*pros::delay(7000);

  EZchassis.set_turn_pid(44, 100);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(68.5, 127, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-43, 80);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(5, 80, true);
  EZchassis.wait_drive();

  pros::delay(200);

  launchCata();

  EZchassis.set_drive_pid(-1, 80, true);
  EZchassis.wait_drive();

  bandRelease.set_value(true);

  EZchassis.set_turn_pid(88, 100);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(48, 80, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(0, 100);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(47, 80, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-90, 100);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-7.75, 80, true);
  EZchassis.wait_drive();

  spinRoller(100);
  */

}

void skills(){

  EZchassis.set_drive_pid(-5, 120, true);
  EZchassis.wait_drive();
  
  spinRoller(660, true);

  EZchassis.set_drive_pid(3, 120, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(134, 60);
  EZchassis.wait_drive();

  intake.move_velocity(600);

  EZchassis.set_drive_pid(-19, 90, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(89, 60);
  EZchassis.wait_drive();

  pros::delay(300);

  intake = 0;

  EZchassis.set_drive_pid(-11, 120, true);
  EZchassis.wait_drive();
  
  spinRoller(660, true);

  EZchassis.set_drive_pid(6, 80, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(1, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(59, 120, true);
  EZchassis.wait_drive();

  launchCata();

  EZchassis.set_drive_pid(-47, 120, true);

  cataReturn();

  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-133, 60);
  EZchassis.wait_drive();

  intake = 127;

  EZchassis.set_drive_pid(-60, 60, true);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(1, 60, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-43, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(7, 120, true);

  pros::delay(100);

  launchCata();

  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-8, 100, true);

  cataReturn();

  EZchassis.wait_drive();

  intake = 0;

  EZchassis.set_turn_pid(-133, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-34, 80);
  EZchassis.wait_drive();

  intake = 127;

  EZchassis.set_drive_pid(-30, 40, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-89, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(45.5, 120, true);
  EZchassis.wait_drive();

  intake = 0;

  launchCata();

  EZchassis.set_drive_pid(-31, 120, true);
  
  cataReturn();

  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-44, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-22, 90, true);
  EZchassis.wait_drive();

  intake = 127;

  EZchassis.set_drive_pid(-33, 40, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-177, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(31, 120, true);
  EZchassis.wait_drive();

  intake = 0;
  
  launchCata();

  EZchassis.set_drive_pid(-42, 120, true);

  cataReturn();

  EZchassis.wait_drive();

  EZchassis.set_turn_pid(44, 60);
  EZchassis.wait_drive();

  intake = 127;

  EZchassis.set_drive_pid(-60, 60, true);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(1, 60, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(134, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(7, 120, true);

  pros::delay(100);

  launchCata();

  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-8, 100, true);

  cataReturn();

  EZchassis.wait_drive();

  EZchassis.set_turn_pid(44, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-35, 80, true);
  EZchassis.wait_drive();

  intake = 127;

  EZchassis.set_drive_pid(-26, 40, true);
  EZchassis.wait_drive();
  
  EZchassis.set_turn_pid(89, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(44, 120, true);
  EZchassis.wait_drive();

  intake = 0;

  launchCata();

  EZchassis.set_drive_pid(-45, 120, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(44, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(112, 120, true);

  cataReturn();

  EZchassis.wait_drive();

  EZchassis.set_turn_pid(178, 60);
  EZchassis.wait_drive();

  intake = 127;

  EZchassis.set_drive_pid(-30, 100, true);
  EZchassis.wait_drive();

  pros::delay(500);

  intake = 0;

  EZchassis.set_drive_pid(-6.5, 50, true);
  EZchassis.wait_drive();

  spinRoller(260, true);

  EZchassis.set_drive_pid(24, 100, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(268, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-13.5, 50, true);
  EZchassis.wait_drive();

  spinRoller(260, true);

  EZchassis.set_drive_pid(23, 100, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(233, 60);
  EZchassis.wait_drive();

  intake = 127;

  EZchassis.set_drive_pid(-23, 100, true);
  EZchassis.wait_drive();

  intake = 0;

  //EXPAND EXPAND EXPAND



  /*intake = 127;

  EZchassis.set_drive_pid(65, 120, true);
  EZchassis.wait_drive();

  intake = 0;

  EZchassis.set_turn_pid(10, 60);
  EZchassis.wait_drive();
  
  launchCata();

  EZchassis.set_turn_pid(0, 60);
  EZchassis.wait_drive();
  
  EZchassis.set_drive_pid(-36, 120, true);

  cataReturn();

  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-43, 60);
  EZchassis.wait_drive();

  intake = 127;

  EZchassis.set_drive_pid(-25, 60, true);
  EZchassis.wait_drive();

  pros::delay(300);

  EZchassis.set_drive_pid(-30, 40, true);
  EZchassis.wait_drive();

  pros::delay(50);

  EZchassis.set_drive_pid(53.5, 120, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(0, 60);
  EZchassis.wait_drive();

  intake = -127;

  EZchassis.set_drive_pid(38, 120, true);
  EZchassis.wait_drive();

  intake = 0;

  EZchassis.set_turn_pid(10, 70);
  EZchassis.wait_drive();

  launchCata();

  EZchassis.set_turn_pid(0, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-56, 127, true);

  cataReturn();

  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-132, 60);
  EZchassis.wait_drive();

  intake = 127;

  EZchassis.set_drive_pid(-65, 60, true);
  EZchassis.wait_drive();

  pros::delay(500);

  EZchassis.set_drive_pid(3, 60, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-43, 60);
  EZchassis.wait_drive();

  intake = 0;

  EZchassis.set_drive_pid(8, 127, true);

  launchCata();

  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-7.5, 120, true);

  cataReturn();

  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-132, 60);
  EZchassis.wait_drive();

  intake = 127;

  EZchassis.set_drive_pid(-25, 120, true);
  EZchassis.wait_drive();

  pros::delay(400);

  EZchassis.set_drive_pid(-34, 30, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-84, 60);
  EZchassis.wait_drive();

  intake = -127;

  EZchassis.set_drive_pid(54, 127, true);
  EZchassis.wait_drive();

  intake = 0;

  EZchassis.set_turn_pid(-100, 60);
  EZchassis.wait_drive();

  launchCata();

  EZchassis.set_turn_pid(-87, 60);
  EZchassis.wait_drive();

  cataReturn();

  EZchassis.set_drive_pid(-34, 127, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-45, 60);
  EZchassis.wait_drive();

  intake = 127;

  EZchassis.set_drive_pid(-25, 120, true);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-38, 40, true);
  EZchassis.wait_drive();

  pros::delay(500);

  EZchassis.set_turn_pid(174, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(34, 120, true);
  EZchassis.wait_drive();

  intake = 0;

  EZchassis.set_turn_pid(190, 60);
  EZchassis.wait_drive();

  launchCata();

  EZchassis.set_turn_pid(178, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-58, 120, true);

  cataReturn();

  EZchassis.wait_drive();

  EZchassis.set_turn_pid(269, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-7.5, 120, true);
  EZchassis.wait_drive();

  spinRoller(620);

  EZchassis.set_drive_pid(18, 120, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(179, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-21.5, 120, true);

  intake = 127;

  pros::delay(200);

  intake = 0;

  EZchassis.wait_drive();

  spinRoller(620);

  EZchassis.set_drive_pid(23, 120, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(220, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-18, 70, true);
  EZchassis.wait_drive();

  expansion.set_value(true);

  pros::delay(1300);

  EZchassis.set_drive_pid(10, 120, true);
  EZchassis.wait_drive();
  */


}

void rightSide(){

  EZchassis.set_drive_pid(17, 100, true);

  cataReturn();

  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-89, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-6, 100, true);
  EZchassis.wait_drive();

  spinRoller(260);

  /*EZchassis.set_drive_pid(10, 100, true);
  EZchassis.wait_drive();*/

  EZchassis.set_drive_pid(3, 120, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-77, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(7, 120);

  pros::delay(40);

  launchCata();

  EZchassis.wait_drive();

  EZchassis.set_turn_pid(0, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-6, 100, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(45, 60);
  EZchassis.wait_drive();

  cataReturn();

  intake = 127;

  EZchassis.set_drive_pid(-56, 60, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-44, 80);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(3, 60, true);
  EZchassis.wait_drive();

  launchCata();
  
  pros::delay(1000);

  intake = 0;

  bandRelease.set_value(true);

  /*EZchassis.set_turn_pid(-65, 100);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-20, 100, true);
  EZchassis.wait_drive();

  */cataReturn();


  /*EZchassis.set_turn_pid(0, 80);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-5, 100, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(45, 80);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-62, 100, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-43, 80);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(10, 100, true);
  EZchassis.wait_drive();

  launchAssistedCata();

  bandRelease.set_value(true);
  */
}

void fullWinPoint(){

  EZchassis.set_drive_pid(17, 100, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-89, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-6, 100, true);
  EZchassis.wait_drive();

  spinRoller(280);

  EZchassis.set_drive_pid(6, 100, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-134, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(61, 100, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-44, 80);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-6, 60, true);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(16, 50, true);

  pros::delay(300);

  launchCata();

  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-7, 80, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(15, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-40, 120, true);
  EZchassis.wait_drive();

  bandRelease.set_value(true);
  
  cataReturn();

  EZchassis.set_turn_pid(-100, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(36, 80, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(0, 60);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-5, 60, true);
  EZchassis.wait_drive();

  spinRoller(280);

}

void testAuton(){
  
  EZchassis.set_turn_pid(90, 100);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(3, 127, true);
  EZchassis.wait_drive();

}