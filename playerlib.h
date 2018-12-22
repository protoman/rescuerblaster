#ifndef PLAYER_H
#define PLAYER_H


#include <iostream>
#include "defines.h"
#include "mediator.h"

class playerlib
{
public:
    playerlib();

    void setInput(int commands[INPUT_COMMAND_COUNT]);
    void move();
    double get_x();
    double get_y();
    bool can_move_x(double xinc);
    bool can_move_y(double yinc);

    unsigned int getLives() const;
    unsigned int getBombs() const;
    unsigned int getPoints() const;

    e_DIRECTION getDirection() const;

    double getFly_accel() const;

    double getFly_speed() const;

private:
    double pos_x;
    double pos_y;
    double xinc;
    double yinc;
    double fly_speed;
    double fly_accel;
    int input_commands[INPUT_COMMAND_COUNT];
    unsigned int lives;
    unsigned int bombs;
    unsigned int points;
    e_DIRECTION direction;
};

#endif // PLAYER_H
