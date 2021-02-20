#include "main.h"


void drivestraight(int power, int distance, char direction, float kp){
  int error = 0;
  resetSensors();
  if(direction == 'f'){
    while(leftPosition() <= distance ){
      error = distance - leftPosition();
      setPower(error*kp, 0);
    }
    stopAllMotors();
  }

  else if(direction == 'b'){
    while(leftPosition() >= -distance ){
      error = distance - leftPosition();
      setPower(-error*kp, 0);
    }
    stopAllMotors();
  }
}

void gyro_turn(int degree, char direction){
  resetSensors();
  double kp = 0.1;
  int error = 0;
  int power = 0;
  if(direction == 'L'){
    while(gyro.get_value() <= degree){
      error = -degree - gyro.get_value();
      power = kp*power;
      //need to tested
      //leftFrontMotor = -power;
      //leftBackMotor = -power;
      //rightFrontMotor = -power;
      //rightBackMotor = -power;
      setPower(0, -power);
    }
  }
  else if(direction == 'R'){
    while(gyro.get_value() >= degree){
      error = degree + gyro.get_value();
      power = -kp*power;
      //leftFrontMotor = power;
      //leftBackMotor = power;
      //rightFrontMotor = power;
      //rightBackMotor = power;
      setPower(0, power);
    }
  }
}

void shoot(int time){
	indexer = -127;
	roller = 127;
	delay(time);
	indexer = 0;
	roller = 0;
}

void intake(int state){
  if(state == 1){
    leftIntake = 127;
    rightIntake = -127;
    roller = 127;
  }
  else if(state == 2){
    leftIntake = -127;
    rightIntake = 127;
    roller = -127;
  }
  else if(state == 0){
    leftIntake = 0;
    rightIntake = 0;
    roller = 0;
  }
}
