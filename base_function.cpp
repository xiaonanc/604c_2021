#include "main.h"
#include "base_function.hpp"

void stopAllMotors(){
  leftFrontMotor = 0;
  leftBackMotor = 0;
  rightFrontMotor = 0;
  rightBackMotor = 0;
}

void setPower(double power, double turn){
  leftFrontMotor = turn + power;
  leftBackMotor = turn + power;
  rightFrontMotor = turn - power;
  rightBackMotor = turn - power;
}

void resetSensors(){
  leftFrontMotor.tare_position();
  leftBackMotor.tare_position();
  rightFrontMotor.tare_position();
  rightBackMotor.tare_position();
  gyro.reset();
}

double leftPosition(){
  return leftFrontMotor.get_position();
}

double rightPosition(){
  return rightFrontMotor.get_position();
}
