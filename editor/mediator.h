#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <iostream>
#include <vector>
#include <map>

#include "file_stage.h"
#include "file_map.h"
#include "file_io.h"


class Mediator
{
public:
    Mediator();
    static Mediator* get_instance();
    //Mediator(Mediator const&){}             // copy constructor is private
    //Mediator& operator=(Mediator const&){}  // assignment operator is private
    void save();
    void loadMapData();
    void load();

public:
    std::vector<st_file_stage> stage_list;
    std::map<int, std::vector<st_file_map>> map_list_map;

    unsigned int currentStage;
    unsigned int currentMap;

private:
    static Mediator* _instance;

};

#endif // MEDIATOR_H
