#ifndef FILE_MAP_H
#define FILE_MAP_H

#include "defines.h"

enum e_ground_type {
    GROUND_TYPE_NORMAL,
    GROUND_TYPE_WATER,
    GROUND_TYPE_LAVA,
    GROUND_TYPE_COUNT
};


struct st_file_map {
    int tile[MAP_W][MAP_H];
    e_ground_type ground_type;
    int north;
    int south;
    int west;
    int east;


    st_file_map() {
        for (int i=0; i<MAP_W; i++) {
            for (int j=0; j<MAP_H; j++) {
                tile[i][j] = 0;
            }
        }
        north = -1;
        south = -1;
        west = -1;
        east = -1;
    }
};
/*
// 924910, a56022, b67932
    146, 73, 16
    165, 96, 34
    182, 121, 50


// 434243, 676668, 8f918f
    67, 66, 67
    103, 102, 104
    143, 145, 143

// 0a2ea0, 1d4bbc, 3b71d1
    10, 46, 160
    29, 75, 188
    59, 113, 209


*/

#endif // FILE_MAP_H
