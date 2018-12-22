#ifndef TIMERLIB_H
#define TIMERLIB_H

#include <SDL2/SDL.h>
#include <iostream>

class timerlib
{
public:
    timerlib();
    unsigned long getTimer() const;
    bool isPaused();
    void delay(Uint32 delay_ms);
    void start();
    unsigned long getCurrentTime();

private:
    bool _paused;
    long _ticks;
    unsigned long _paused_ticks;
    long _paused_timer;
    unsigned long _start_timer;

};

#endif // TIMERLIB_H
