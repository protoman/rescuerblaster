#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <iostream>
#include <vector>

#include "file/file_stage.h"
#include "file/file_map.h"
#include "file/file_io.h"


class GameMediator
{
public:
    GameMediator();
    static GameMediator* get_instance();
    //Mediator(Mediator const&){}             // copy constructor is private
    //Mediator& operator=(Mediator const&){}  // assignment operator is private
    void load();
    bool can_move_x(double x, double y, int w, int h, double xinc);
    bool can_move_y(double x, double y, int w, int h, double yinc);

public:
    std::vector<st_file_stage> stage_list;
    std::map<int, std::vector<st_file_map>> map_list_map;
    unsigned short currentStage;
    unsigned short currentMap;
    int player_w, player_h;


private:
    static GameMediator* _instance;

};

#endif // MEDIATOR_H
