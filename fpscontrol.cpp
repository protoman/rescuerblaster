#include "fpscontrol.h"
#include <iostream>
#include "timerlib.h"

fpscontrol::fpscontrol() : fps_timer(0)
{
    fps_max = DEFAULT_FPS_MAX;
    fps_counter = 0;
    fps_min_fail_count = 0;
    failed_min_fps = false;
}

void fpscontrol::initialize()
{
    max_frame_ticks = (1000.0/(float)fps_max)+0.00001;
    frame_count = 0;
    last_second_ticks = timer.getTimer();
    /*
    fps_max = max;
    float percent = (100 * fps_max) / DEFAULT_FPS_MAX;
    std::cout << "FPS_CONTROL.set_max_fps[" << max << "], percent[" << percent << "]" << std::endl;
    max_frame_ticks = (1000.0/(float)fps_max)+0.00001;
    */
}

bool fpscontrol::limit()
{
    if (timer.isPaused()) {
        return true;
    }
    ++frame_count;
    target_ticks = last_second_ticks + static_cast<unsigned int>(frame_count * max_frame_ticks);
    current_ticks = timer.getTimer();
    //std::cout << "fps_control::limit::timer.ticks[" << timer.getTimer() << "], sdl.ticks[" << current_ticks << "]" << std::endl;

    average_ticks += current_ticks - last_frame_ticks;
    if (current_ticks - last_frame_ticks <= min_ticks)
    {
        min_ticks = current_ticks - last_frame_ticks;
    }

    if (current_ticks - last_frame_ticks >= max_frame_ticks)
    {
        max_ticks = current_ticks - last_frame_ticks;
    }

    if (current_ticks < target_ticks)
    {
        timer.delay(target_ticks - current_ticks);
        current_ticks = timer.getTimer();
    }

    last_frame_ticks = current_ticks;

    if (current_ticks - last_second_ticks >= 1000)
    {
        data.fps = frame_count;
        data.frame_average = average_ticks / frame_count;
        data.frame_min = min_ticks;
        data.frame_max = max_ticks;

        frame_count = 0;
        min_ticks = 1000;
        max_ticks = 0;
        average_ticks = 0;
        last_second_ticks = timer.getTimer();
        return true;
    }

    return false;
}



// ********************************************************************************************** //
//                                                                                                //
// ********************************************************************************************** //
void fpscontrol::fps_count()
{
    if (timer.isPaused()) {
        return;
    }
    fps_counter++;
    if (fps_timer <= timer.getTimer()) {
        sprintf(_fps_buffer, "FPS: %d", fps_counter);
        if (fps_counter <= DEFAULT_FPS_MAX-4) {
            frame_drop_period = DEFAULT_FPS_MAX/(DEFAULT_FPS_MAX-fps_counter);
            //std::cout << "frame_drop_period[" << frame_drop_period << "], fps_counter[" << fps_counter << "]" << std::endl;
        } else {
            frame_drop_period = 0;
        }
        fps_counter = 0;
        fps_timer = timer.getTimer()+1000;
    }
    if (fps_counter > 1) {
        if (fps_counter <= FPS_MINIMAL_LIMIT) {
            fps_min_fail_count++;
        } else {
            fps_min_fail_count = 0;
        }
        if (fps_min_fail_count >= FPS_MINIMAL_MAX_FAIL) {
            failed_min_fps = true;
        }
        std::string temp_str(_fps_buffer);
        //graphLib.draw_text(12, 2, temp_str);
    }
}

int fpscontrol::get_current_frame_n()
{
    return fps_counter;
}

int fpscontrol::get_frame_drop_n()
{
    if (frame_drop_period < 2) {
        return 2;
    }
    return frame_drop_period;
}

bool fpscontrol::get_failed_min_fps()
{
    return failed_min_fps;
}

void fpscontrol::reset_failed_min_fps()
{
    failed_min_fps = false;
}



