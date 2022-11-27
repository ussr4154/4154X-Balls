#include "main.h"
using namespace okapi;

std::shared_ptr<OdomChassisController> chassis =
  ChassisControllerBuilder()
    .withMotors({8,10,9},{5,7,6})
    .withDimensions({AbstractMotor::gearset::blue, (60.0 / 36.0)}, {{3.25_in, 11.25_in}, imev5BlueTPR})
    .withOdometry()
    .buildOdometry();

// Chassis constructor
Drive EZchassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {1, 2, 3}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{6, 5, 4}

  // IMU Port
  ,10

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
  EZchassis.set_pid_constants(&EZchassis.headingPID, 11, 0, 20, 0);
  EZchassis.set_pid_constants(&EZchassis.forward_drivePID, 0.45, 0, 5, 0);
  EZchassis.set_pid_constants(&EZchassis.backward_drivePID, 0.45, 0, 5, 0);
  EZchassis.set_pid_constants(&EZchassis.turnPID, 5, 0.003, 35, 15);
  EZchassis.set_pid_constants(&EZchassis.swingPID, 7, 0, 45, 0);
}

std::shared_ptr<AsyncMotionProfileController> profileController = 
  AsyncMotionProfileControllerBuilder()
    .withLimits({
      4.0, // Maximum linear velocity of the Chassis in m/s
      2.5, // Maximum linear acceleration of the Chassis in m/s^2
      1.0 // Maximum linear jerk of the Chassis in m/s^3
    })
    .withOutput(chassis)
    .buildMotionProfileController();


void spinRoller(int theta, bool rev = false){
  intake.tare_position();
  
  if(rev){
    while(fabs(intake.get_position()) < theta){
    intake = 70;
    }
  }
  else {
    while(fabs(intake.get_position()) < theta){
      intake = -70;
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


void fullWinPoint(){

}

void fiveDisc(){
  
}

void skills(){

}

void testAuton(){
  
}