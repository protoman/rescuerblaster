#ifndef INPUTLIB_H
#define INPUTLIB_H

#include<iostream>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_events.h>
#include "defines.h"


class inputlib
{
public:
    inputlib();
    void init();
    void read();
    int getKey(e_input_commands key_n);
    int* getKeys();
    void quit();

private:
    SDL_Joystick* game_controller;

    int input_commands[INPUT_COMMAND_COUNT];
};

#endif // INPUTLIB_H
