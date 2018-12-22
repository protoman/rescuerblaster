#include "mediator.h"

// Global static pointer used to ensure a single instance of the class.
GameMediator* GameMediator::_instance = nullptr;


GameMediator::GameMediator()
{
    currentStage = 0;
    currentMap = 0;
    player_w = 0;
    player_h = 0;
}

GameMediator *GameMediator::get_instance()
{
    if (!_instance) {
        _instance = new GameMediator();
    }
    return _instance;
}

void GameMediator::load()
{
    stage_list = file_io::load_from_disk<st_file_stage>("data/stage.dat");
    if (stage_list.size() == 0) {
        _instance->stage_list.push_back(st_file_stage());

    }

    char map_filename[512];
    for (unsigned int i=0; i<stage_list.size(); i++) {
        sprintf(map_filename, "data/stage_%d_map.dat", i);

        std::cout << "Mediator::load, stage[" << i << "], stage_list.size[" << stage_list.size() << "]" << std::endl;

        std::vector<st_file_map> map_list;
        map_list_map.insert(std::pair<int, std::vector<st_file_map>>(currentStage, map_list));
        map_list_map.at(currentStage) = file_io::load_from_disk<st_file_map>(std::string(map_filename));

        /*
        for (int j=0; j<map_list_map.at(currentStage).size(); j++) {
            for (int x=0; x<MAP_W; x++) {
                for (int y=0; y<MAP_H; y++) {
                    std::cout << "map[" << j << "].tile[" << x << "][" << y << "]: [" << map_list_map.at(currentStage).at(j).tile[x][y] << "]" << std::endl;
                }
            }

        }
        */

        if (map_list_map.at(currentStage).size() == 0) {
            map_list_map.at(currentStage).push_back(st_file_map());
        }
    }
}

bool GameMediator::can_move_x(double x, double y, int w, int h, double xinc)
{

    if (xinc == 0.0) {
        return true;
    }

    // out of screen
    if (xinc < 0 && x < 0) {
        return true;
    }
    if (xinc > 0 && x > SCREEN_WIDTH) {
        return true;
    }

    st_file_map current_map = map_list_map.at(currentStage).at(currentMap);
    if (xinc > 0) {
        x += w-1;
    } else if (xinc < 0) {
        x++;
    }

    for (int i=0; i<h; i++) {
        int currentTile = current_map.tile[(int)x/TILESIZE][(int)(y+i)/TILESIZE];
        int nextTile = current_map.tile[(int)(x+xinc)/TILESIZE][(int)(y+i)/TILESIZE];
        if (currentTile == 0 && nextTile == 1) {
            //std::cout << "Mediator::can_move_x - X-BLOCKED, xinc[" << xinc << "], pos[" << (int)x << "][" << (int)(y+i) << "][" << i << "], tile[" << (int)x/TILESIZE << "][" << (int)y/TILESIZE << "]" << std::endl;
            return false;
        }
    }

    //std::cout << "Mediator::can_move_x - xinc[" << xinc << "] - TRUE" << std::endl;
    return true;
}


bool GameMediator::can_move_y(double x, double y, int w, int h, double yinc)
{
    if (yinc == 0.0) {
        return true;
    }

    // out of screen
    if (yinc < 0 && y < 0) {
        return true;
    }
    if (yinc > 0 && y > VISIBLE_HEIGHT) {
        return true;
    }


    st_file_map current_map = map_list_map.at(currentStage).at(currentMap);
    //std::cout << "currentStage[" << currentStage << "], currentMap[" << currentMap << "]" << std::endl;

    if (yinc > 0) {
        y += h;
    } else if (yinc < 0) {
        y++;
    }

    for (int i=0; i<w; i++) {
        int tileX = (int)(x+i)/TILESIZE;
        int currentTileY = (int)y/TILESIZE;
        int nextTileY = (int)(y+yinc)/TILESIZE;
        int currentTile = current_map.tile[tileX][currentTileY];
        int nextTile = current_map.tile[tileX][nextTileY];
        if (currentTile == 0 && nextTile == 1) {
            //std::cout << "tileX[" << tileX << "], player.y[" << y << "], yinc[" << yinc << "], currentTileY[" << currentTileY << "], nextTileY[" << nextTileY << "] - BLOCKED" << std::endl;
            //std::cout << "Mediator::can_move_x - Y-BLOCKED, pos[" << (int)x << "][" << (int)(y+i) << "][" << i << "], tile[" << (int)x/TILESIZE << "][" << (int)y/TILESIZE << "]" << std::endl;
            return false;
        }
    }

    return true;
}

