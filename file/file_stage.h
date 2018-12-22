#ifndef FILE_STAGE_H
#define FILE_STAGE_H

#include <iostream>

enum e_STAGE_COLOR {
    STAGE_COLOR_1,
    STAGE_COLOR_2,
    STAGE_COLOR_3,
    STAGE_COLOR_SEPARATOR,
    STAGE_COLOR_BACKGROUND,
    STAGE_COLOR_WATER,
    STAGE_COLOR_COUNT
};



struct st_file_color {
    int r;
    int g;
    int b;

    st_file_color() {
        r = 0;
        g = 0;
        b = 0;
    }

    st_file_color(int set_r, int set_g, int set_b) {
        r = set_r;
        g = set_g;
        b = set_b;
    }
};

struct st_file_stage {
    st_file_color map_color[STAGE_COLOR_COUNT];
    char tilelset[512];
    char background[512];

    st_file_stage() {
        sprintf(tilelset, "\0");
        sprintf(background, "\0");
    }
};


#endif // FILE_STAGE_H
