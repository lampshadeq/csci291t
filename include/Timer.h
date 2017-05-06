#ifndef TIMER_H
#define TIMER_H

#include <ctime>

class Timer {
  public:
    Timer();
    ~Timer();

    clock_t getTicks();
    bool    isPaused();
    bool    isStarted();
    bool    isStopped();
    void    pause();
    void    reset();
    void    resume();
    void    start();
    void    stop();

  private:
    bool    started, paused;
    clock_t startTime, pauseTime;
};

#endif
