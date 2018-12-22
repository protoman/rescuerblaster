#ifndef GRAPHLIB_H
#define GRAPHLIB_H

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "defines.h"
#include "mediator.h"
#include "timerlib.h"

struct st_size {
    int w;
    int h;

    st_size() {
        w = 0;
        h = 0;
    }

    st_size(int set_w, int set_h) {
        w = set_w;
        h = set_h;
    }
};

class graphlib
{
public:
    graphlib();
    ~graphlib();
    void init();
    void delay(Uint32 time_ms);
    void drawScreen();
    void drawPlayer(double x, double y, e_DIRECTION direction, double playerAccel, double playerSpeed);
    void drawHud(unsigned int lives, unsigned int bombs, unsigned int points, unsigned long timeTotal, unsigned long timeLeft);
    void updateScreen();
    SDL_Texture* loadTexture( std::string filename );

    void quit();

private:
    SDL_Surface *SDLSurfaceFromFile(std::string filename);
    void copySDLPortion(int x, int y, int w, int h, SDL_Texture *gTexture);
    void copySDLPortion(int x, int y, int w, int h, int dest_x, int dest_y, SDL_Texture *gTexture);

private:
     SDL_Window* window;
     SDL_Surface* screenSurface;
     SDL_Renderer* gRenderer;
     timerlib tlib;

     SDL_Texture *tileset;
     SDL_Texture *background;
     SDL_Texture *player_texture;
     SDL_Texture *upperland_texture;
     SDL_Texture *livestexture;
     st_size livestexture_size;
     SDL_Texture *bombstexture;
     st_size bombstexture_size;
     SDL_Texture *powertexture;
     SDL_Texture *helicetexture;
     int hud_item_spacer;
     int hud_total_w;
     int hud_bar_w;
     int hud_bar_x;

     int upperland_logo_w, upperland_logo_h;
     int lava_color_count;
     bool lava_color_direction;
     int helice_frame;
     long helice_frame_timer = 0;


     Mix_Music *gMusic = NULL;
};

#endif // GRAPHLIB_H
