#include "main.h"
#include "function.hpp"

//drive straight function
void driveStraight(double target, double kp, double min, double range){
  //initializing variables
  Timer timer;
  bool exit = false;
  int error = 0;
  bool in_range = false;
  double gyro_error = 0;
  double gyro_kp = 0.1;
  //reset gyro and encoder value
  resetSensors();

  //loop while not at the target
  while(exit == false){
    //checks whether I am in the range of the target
    in_range = fabs(leftPosition()) > (fabs(target) - fabs(range));
    //calculates the error
    //distance error
    error = target - leftPosition();
    //angle error
    gyro_error = -gyro.get_value();

    //switch the sign of the min value based on the sign of the error
    if((error > 0 && min < 0) || (error < 0 && min > 0)){
      min *= -1;
    }


    //power the drive with filtered error value
    setPower((error*kp) + min, gyro_error*gyro_kp);

    //check if in range
    if(in_range){
      //if delta time is greater or equal to set value
      //exsit the loop
      if(timer.get_time() >= 250){
        exit = true;
      }
    }
    //if not in range, update start time value
    else{
      timer.start_timer();
    }
  }
  // stop all drive motor after the loop ends
  stopAllMotors();
}

//gyro turn function function
void gyro_turn(double target, double kp, double min, double range){
  // reset gyro and encoder value
  resetSensors();
  //initializing variables
  Timer timer;
  bool exit = false;
  int error = 0;
  bool in_range = false;
  double power = 0;
  //loop while not at target
  while(exit == false){
    //checks whether robot is in range
    in_range = fabs(gyro.get_value()) > (fabs(target) - fabs(range));
    //calculating angle error for the turn
    error = target - gyro.get_value();
    //switch the sign of the min value based on the sign of the error
      if((error > 0 && min < 0) || (error < 0 && min > 0)){
        min *= -1;
      }
    //calculating power with filtured error value
    power = (kp*error) + min;
    //powering the drive
    setPower(0, power);

    //check if in range
    if(in_range){
      //updating delta time

      //exsit if the delta time is bigger or equal to set value
      if(timer.get_time()>= 100){
        exit = true;
      }
    }
    //update start time if not in range
    else{
      timer.start_timer();
    }
  }
  //stop all drive motors
  stopAllMotors();
}

//shoot function
void shoot(int time){
	indexer = -127;
	roller = 127;
	delay(time);
	indexer = 0;
	roller = 0;
}

//intake function
void intake(int state){
  //intake
  if(state == 1){
    leftIntake = 127;
    rightIntake = -127;
    roller = 127;
  }
  //outake
  else if(state == 2){
    leftIntake = -127;
    rightIntake = 127;
    roller = -127;
  }
  //stop intake motors
  else if(state == 0){
    leftIntake = 0;
    rightIntake = 0;
    roller = 0;
  }
}
