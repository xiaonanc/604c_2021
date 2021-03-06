#include "timer.hpp"
#include "main.h"

Timer::Timer(){
  start_time = 0;
}

double Timer::get_time(){
  return millis() - start_time;
}

void Timer::start_timer(){
  start_time = millis();
}
