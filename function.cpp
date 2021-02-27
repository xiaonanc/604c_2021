#include "main.h"
#include "function.hpp"

//need to be tested
//gyro_kp needs to be tuned
//line 22 needs to be tuned
void driveStraight(double target, double kp, double min, double range){
  bool exit = false;
  double start_time = millis();
  double delta = 0;
  int error = 0;
  bool in_range = false;
  double gyro_error = 0;
  double gyro_kp = 0.1;

  resetSensors();

  while(exit == false){
    in_range = fabs(leftPosition()) > (fabs(target) - fabs(range));
    error = target - leftPosition();
    gyro_error = -gyro.get_value();
    setPower((error*kp) + min, gyro_error*gyro_kp);

    if(in_range){
      //the 250 need to be tuned
      delta = millis() - start_time;
      if(delta >= 250){
        exit = true;
      }
    }
    else{
      start_time = millis();
    }
  }
  stopAllMotors();
}

//need to be tested
//kp = 0.1 works
//range = 46 works
void gyro_turn(double target, double kp, double min, double range){
  resetSensors();
  bool exit = false;
  double start_time = millis();
  double delta = 0;
  int error = 0;
  bool in_range = false;
  double power = 0;

  while(exit == false){
    in_range = fabs(gyro.get_value()) > (fabs(target) - fabs(range));
    error = target - gyro.get_value();
    power = (kp*error) + min;
    setPower(0, power);

    if(in_range){
      //delta needs to be tuned
      delta = millis() - start_time;
      if(delta > 250){
        exit = true;
      }
    }
    else{
      start_time = millis();
    }
  }
  stopAllMotors();
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
