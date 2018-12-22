#include "playerlib.h"

#define MAX_SPEED 6.2
const double ACCEL = 0.1;
const double MAX_ACCEL = 0.05;

playerlib::playerlib()
{
    pos_x = TILESIZE*4;
    pos_y = 0;
    fly_speed = 0.1; // falling speed
    fly_accel = 0.0;  // falling accel
    lives = 3;
    bombs = 6;
    points = 0;
    direction = DIRECTION_RIGHT;
}

void playerlib::setInput(int commands[INPUT_COMMAND_COUNT])
{
    for (unsigned int i=0; i<INPUT_COMMAND_COUNT; i++) {
        input_commands[i] = commands[i];
    }
}

void playerlib::move()
{
    xinc = 0;
    yinc = 0;
    // gravity
    if (input_commands[INPUT_COMMAND_FLY] != 1) {
        //std::cout << "PLAYER::MOVE - FALL, fly_accel[" << fly_accel << "]" << std::endl;
        if (fly_accel < MAX_ACCEL && can_move_y(1.0)) {
            //std::cout << "MOVE, INC ACCEL" << std::endl;
            fly_accel = fly_accel + ACCEL;
        }
    } else {
        std::cout << "PLAYER::MOVE - FLY, fly_accel[" << fly_accel << "]" << std::endl;
        if (fly_accel > -MAX_ACCEL) {
            std::cout << "MOVE, DEC ACCEL" << std::endl;
            fly_accel = fly_accel - ACCEL;
        }
    }

    if (input_commands[INPUT_COMMAND_X_AXIS] == 1) {
        xinc += MAX_SPEED;
    } else if (input_commands[INPUT_COMMAND_X_AXIS] == -1) {
        xinc -= MAX_SPEED;
    }

    if (fly_accel > 0 && fly_speed < MAX_SPEED) {
        fly_speed += fly_accel;
    } else if (fly_accel < 0 && fly_speed > -MAX_SPEED) {
        fly_speed += fly_accel;
    }

    yinc += fly_speed;
    if (xinc > 0) {
        for (double i=xinc; i>1.0; i-=1.0) {
            if (can_move_x(i)) {
                pos_x += i;
                break;
            }
        }
        direction = DIRECTION_RIGHT;
    } else if (xinc < 0) {
        for (double i=xinc; i<-1.0; i+=1.0) {
            if (can_move_x(i)) {
                pos_x += i;
                break;
            }
        }
        direction = DIRECTION_LEFT;
    }

    if (yinc >= 1.0) {
        bool moved_y = false;
        for (double i=yinc; i>1.0; i-=1.0) {
            if (can_move_y(i)) {
                moved_y = true;
                pos_y += i;
                break;
            }
        }
        //std::cout << ">>>>>>>>> moved_y[" << moved_y << "], yinc[" << yinc << "], fly_accel[" << fly_accel << "]" << std::endl;
        // SET ACCELL TO ZERO IF ON GROUND
        if (yinc >= 1 && moved_y == false) {
            fly_accel = 0.0;
            fly_speed = 0.0;
            std::cout << "ON-GROUND, RESET ACCEL [" << fly_accel << "]" << std::endl;
        }
    } else if (yinc < 0) {
        for (double i=yinc; i<-1.0; i+=1.0) {
            if (can_move_y(i)) {
                pos_y += i;
                break;
            }
        }
    }


    // SOUTH EXIT
    if (get_y() > VISIBLE_HEIGHT && GameMediator::get_instance()->map_list_map.at(GameMediator::get_instance()->currentStage).at(GameMediator::get_instance()->currentMap).south != -1) {
        GameMediator::get_instance()->currentMap = GameMediator::get_instance()->map_list_map.at(GameMediator::get_instance()->currentStage).at(GameMediator::get_instance()->currentMap).south;
        pos_y = 0;
    }
    // NORTH EXIT
    if (get_y()+GameMediator::get_instance()->player_h/2 < 0 && GameMediator::get_instance()->map_list_map.at(GameMediator::get_instance()->currentStage).at(GameMediator::get_instance()->currentMap).north != -1) {
        GameMediator::get_instance()->currentMap = GameMediator::get_instance()->map_list_map.at(GameMediator::get_instance()->currentStage).at(GameMediator::get_instance()->currentMap).north;
        pos_y = VISIBLE_HEIGHT;
    }
    // WEST EXIT
    if (get_x() < 0 && GameMediator::get_instance()->map_list_map.at(GameMediator::get_instance()->currentStage).at(GameMediator::get_instance()->currentMap).west != -1) {
        GameMediator::get_instance()->currentMap = GameMediator::get_instance()->map_list_map.at(GameMediator::get_instance()->currentStage).at(GameMediator::get_instance()->currentMap).west;
        pos_x = SCREEN_WIDTH-1;
    }
    // EAST EXIT
    if (get_x() > SCREEN_WIDTH && GameMediator::get_instance()->map_list_map.at(GameMediator::get_instance()->currentStage).at(GameMediator::get_instance()->currentMap).east != -1) {
        GameMediator::get_instance()->currentMap = GameMediator::get_instance()->map_list_map.at(GameMediator::get_instance()->currentStage).at(GameMediator::get_instance()->currentMap).east;
        pos_x = 1;
    }

}

double playerlib::get_x()
{
    return pos_x;
}

double playerlib::get_y()
{
    return pos_y;
}

bool playerlib::can_move_x(double xinc)
{
    int x = pos_x;
    if (direction == DIRECTION_LEFT) {
        x += 24;
    }
    int y = pos_y;
    return GameMediator::get_instance()->can_move_x(x, y, PLAYER_BOX_W, PLAYER_BOX_H, xinc);
}

bool playerlib::can_move_y(double yinc)
{
    //std::cout << "playerlib::can_move_y - yinc[" << yinc << "], pos_y[" << pos_y << "]" << std::endl;
    return GameMediator::get_instance()->can_move_y(pos_x, pos_y, GameMediator::get_instance()->player_w, GameMediator::get_instance()->player_h/2, yinc);
}

unsigned int playerlib::getLives() const
{
    return lives;
}

unsigned int playerlib::getBombs() const
{
    return bombs;
}

unsigned int playerlib::getPoints() const
{
    return points;
}

e_DIRECTION playerlib::getDirection() const
{
    return direction;
}

double playerlib::getFly_accel() const
{
    return fly_accel;
}

double playerlib::getFly_speed() const
{
    return fly_speed;
}
