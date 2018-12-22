#include "inputlib.h"

const int JOYSTICK_DEAD_ZONE = 8000;

inputlib::inputlib()
{
    game_controller = nullptr;
}

void inputlib::init()
{
    //Check for joysticks
    if (SDL_NumJoysticks() < 1) {
        std::cout << "Warning: No joysticks connected!" << std::endl;;
    } else {
        //Load joystick
        game_controller = SDL_JoystickOpen( 0 );
        if (game_controller == nullptr) {
            std::cout << "Warning: Unable to open game controller! SDL Error[" << SDL_GetError() << "]" << std::endl;
        }
    }
}

void inputlib::read()
{
    SDL_Event e;

    for (unsigned int i=0; i<INPUT_COMMAND_COUNT; i++) {
        //input_commands[i] = 0;
    }

    while( SDL_PollEvent( &e ) != 0 ) {
        //User requests quit
        if( e.type == SDL_QUIT ) {
            input_commands[INPUT_COMMAND_QUIT] = 1;
        } else if (e.type == SDL_KEYDOWN) {
            //Select surfaces based on key press
            switch( e.key.keysym.sym )
            {
                case SDLK_UP:
                input_commands[INPUT_COMMAND_Y_AXIS] = -1;
                break;

                case SDLK_DOWN:
                input_commands[INPUT_COMMAND_Y_AXIS] = 1;
                break;

                case SDLK_LEFT:
                input_commands[INPUT_COMMAND_X_AXIS] = -1;
                break;

                case SDLK_RIGHT:
                input_commands[INPUT_COMMAND_X_AXIS] = 1;
                break;

                case SDLK_ESCAPE:
                input_commands[INPUT_COMMAND_QUIT] = 1;
                break;

                case SDLK_x:
                input_commands[INPUT_COMMAND_FLY] = 1;
                break;

                case SDLK_a:
                input_commands[INPUT_COMMAND_BOMB] = 1;
                break;

                default:
                break;
            }

        } else if (e.type == SDL_KEYUP) {
            //Select surfaces based on key press
            switch( e.key.keysym.sym )
            {
                case SDLK_UP:
                input_commands[INPUT_COMMAND_Y_AXIS] = 0;
                break;

                case SDLK_DOWN:
                input_commands[INPUT_COMMAND_Y_AXIS] = 0;
                break;

                case SDLK_LEFT:
                input_commands[INPUT_COMMAND_X_AXIS] = 0;
                break;

                case SDLK_RIGHT:
                input_commands[INPUT_COMMAND_X_AXIS] = 0;
                break;

                case SDLK_ESCAPE:
                input_commands[INPUT_COMMAND_QUIT] = 0;
                break;

                case SDLK_x:
                input_commands[INPUT_COMMAND_FLY] = 0;
                break;

                case SDLK_a:
                input_commands[INPUT_COMMAND_BOMB] = 0;
                break;

                default:
                break;
            }
        } else if (e.type == SDL_JOYAXISMOTION) {
            //Motion on controller 0
            if( e.jaxis.which == 0 ) {
                //X axis motion
                if( e.jaxis.axis == 0 ) {

                    if( e.jaxis.value < -JOYSTICK_DEAD_ZONE ) { //Left of dead zone
                        input_commands[INPUT_COMMAND_X_AXIS] = -1;
                    } else if( e.jaxis.value > JOYSTICK_DEAD_ZONE ) { //Right of dead zone
                        input_commands[INPUT_COMMAND_X_AXIS] =  1;
                    } else {
                        input_commands[INPUT_COMMAND_X_AXIS] = 0;
                    }
                } else if( e.jaxis.axis == 1 ) { //Y axis motion
                    if( e.jaxis.value < -JOYSTICK_DEAD_ZONE ) { //Below of dead zone
                        input_commands[INPUT_COMMAND_Y_AXIS] = -1;
                    } else if( e.jaxis.value > JOYSTICK_DEAD_ZONE ) { //Above of dead zone
                        input_commands[INPUT_COMMAND_Y_AXIS] =  1;
                    } else {
                        input_commands[INPUT_COMMAND_Y_AXIS] = 0;
                    }
                }
            }
        }
    }
}

int inputlib::getKey(e_input_commands key_n)
{
    return input_commands[key_n];
}

int *inputlib::getKeys()
{
    return input_commands;
}

void inputlib::quit()
{
    SDL_JoystickClose(game_controller);
    game_controller = nullptr;
}
