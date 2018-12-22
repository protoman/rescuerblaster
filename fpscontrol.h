#ifndef FPSCONTROL_H
#define FPSCONTROL_H

#include <SDL2/SDL.h>
#include "timerlib.h"

#define DEFULT_PLAYER_SPEED 1.2
#define DEFAULT_FPS_MAX 60
#define FPS_MINIMAL_LIMIT 50            // if fps is lower or equal this value, we increment fail-count
#define FPS_MINIMAL_MAX_FAIL 10         // if we have 10 consecutive times fps is under limit, we take action


struct st_fps_data
{
    unsigned long frame_min;
    unsigned long frame_max;
    double frame_average;
    int fps;
};


class fpscontrol
{
public:
    fpscontrol();
    void initialize();
    bool limit();
    void fps_count();
    int get_current_frame_n();
    int get_frame_drop_n();
    bool get_failed_min_fps();
    void reset_failed_min_fps();

private:
    st_fps_data data;
    float max_frame_ticks;
    unsigned long last_second_ticks;
    int frame_count;

    unsigned long min_ticks;
    unsigned long max_ticks;
    double average_ticks;
    unsigned long last_frame_ticks;

    unsigned long current_ticks;
    unsigned long target_ticks;

    unsigned short fps_max;

    unsigned long fps_timer;
    int fps_counter;
    // if we are getting less than 60 fps, this will tell main loop how many times it will run full until drop one
    int frame_drop_period;
    char _fps_buffer[128];

    unsigned int fps_min_fail_count; // counts the number of sequential times the FPS is under minumal limit
    bool failed_min_fps;

    timerlib timer;
};

#endif // FPSCONTROL_H
