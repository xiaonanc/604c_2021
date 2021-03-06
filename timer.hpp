#ifndef _TIMER_HPP_
#define _TIMER_HPP_

class Timer{
  public:
  double get_time();
  void start_timer();
  Timer();

  private:
  double start_time;

};

#endif
