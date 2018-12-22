#include "timerlib.h"

timerlib::timerlib()
{
    _paused_timer = 0;
    _ticks = 0;
    _paused_ticks = 0;
    _paused = false;
}

unsigned long timerlib::getTimer() const
{
    return SDL_GetTicks() - _paused_ticks;
}

bool timerlib::isPaused()
{
    return false;
}

void timerlib::delay(Uint32 delay_ms)
{
    //std::cout << "timerlib::delay[" << (int)delay_ms << "]" << std::endl;
    SDL_Delay(delay_ms);
}

void timerlib::start()
{
    _start_timer = getTimer();
}

unsigned long timerlib::getCurrentTime()
{
    unsigned long passedTicks = getTimer() - _start_timer;
    return passedTicks/1000;
}
