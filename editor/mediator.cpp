#include "mediator.h"

// Global static pointer used to ensure a single instance of the class.
Mediator* Mediator::_instance = nullptr;


Mediator::Mediator()
{
    currentStage = 0;
    currentMap = 0;
}

Mediator *Mediator::get_instance()
{
    if (!_instance) {
        _instance = new Mediator();
        _instance->stage_list.push_back(st_file_stage());
        std::vector<st_file_map> map_list;
        _instance->map_list_map.insert(std::pair<int, std::vector<st_file_map>>(0, map_list));
    }
    return _instance;
}

void Mediator::save()
{
    file_io::save_data_to_disk<st_file_stage>("data/stage.dat", stage_list);

    char map_filename[512];
    for (unsigned int i=0; i<stage_list.size(); i++) {
        sprintf(map_filename, "data/stage_%d_map.dat", i);
        file_io::save_data_to_disk<st_file_map>(std::string(map_filename), map_list_map.at(i));
    }
}

void Mediator::loadMapData()
{
    char map_filename[512];
    for (unsigned int i=0; i<stage_list.size(); i++) {
        sprintf(map_filename, "data/stage_%d_map.dat", i);
        map_list_map.at(i) = file_io::load_from_disk<st_file_map>(std::string(map_filename));
        if (map_list_map.at(i).size() == 0) {
            map_list_map.at(i).push_back(st_file_map());
        }
    }

}

void Mediator::load()
{
    stage_list = file_io::load_from_disk<st_file_stage>("data/stage.dat");
    if (stage_list.size() == 0) {
        _instance->stage_list.push_back(st_file_stage());

    }
    loadMapData();
}

