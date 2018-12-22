#include <iostream>
#include "defines.h"

#include "graphics/graphlib.h"
#include "input/inputlib.h"
#include "playerlib.h"
#include "fpscontrol.h"
#include "mediator.h"
using namespace std;

std::string FILEPATH;

int main(int argc, char *argv[])
{
    std::string EXEC_NAME;
    #ifndef WIN32
        EXEC_NAME = "rescueblaster";
    #else
        EXEC_NAME = "rescueblaster.exe";
    #endif

    std::string argvString = std::string(argv[0]);
    FILEPATH = argvString.substr(0, argvString.size()-EXEC_NAME.size());

    GameMediator::get_instance()->load();

    graphlib glib;
    inputlib ilib;
    timerlib tlib;
    playerlib player;
    fpscontrol fps;
    glib.init();
    ilib.init();
    tlib.start();
    fps.initialize();

    while (true) {
        ilib.read();
        player.setInput(ilib.getKeys());
        if (ilib.getKey(INPUT_COMMAND_QUIT) == 1) {
            break;
        }
        player.move();
        glib.drawScreen();
        glib.drawPlayer(player.get_x(), player.get_y(), player.getDirection(), player.getFly_accel(), player.getFly_speed());
        glib.drawHud(player.getLives(), player.getBombs(), player.getPoints(), 100, 100-tlib.getCurrentTime());
        glib.updateScreen();
        fps.limit();
    }

    ilib.quit();
    glib.quit();

    return 0;
}
