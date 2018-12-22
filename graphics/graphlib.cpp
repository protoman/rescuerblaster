#include "graphlib.h"

graphlib::graphlib()
{
    window = nullptr;
    screenSurface = nullptr;
    gRenderer = nullptr;
    player_texture = nullptr;
    upperland_texture = nullptr;
    livestexture = nullptr;
    bombstexture = nullptr;
    powertexture = nullptr;
    tileset = nullptr;
    background = nullptr;
    helicetexture = nullptr;

    upperland_logo_w = 0;
    upperland_logo_h = 0;
    lava_color_count = 0;
    lava_color_direction = false;
    helice_frame = 0;
    helice_frame_timer = tlib.getTimer() + 100;
}

graphlib::~graphlib()
{
    if (player_texture != nullptr) {
        SDL_DestroyTexture(player_texture);
    }
    if (upperland_texture != nullptr) {
        SDL_DestroyTexture(upperland_texture);
    }
    if (tileset != nullptr) {
        SDL_DestroyTexture(tileset);
    }
    if (background != nullptr) {
        SDL_DestroyTexture(background);
    }

    if (livestexture != nullptr) {
        SDL_DestroyTexture(livestexture);
    }
    if (bombstexture != nullptr) {
        SDL_DestroyTexture(bombstexture);
    }
    if (powertexture != nullptr) {
        SDL_DestroyTexture(powertexture);
    }
    if (helicetexture != nullptr) {
        SDL_DestroyTexture(helicetexture);
    }

    Mix_FreeMusic( gMusic );
    gMusic = NULL;

}

void graphlib::init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error[" << SDL_GetError() << "]" << std::endl;
        exit(EXIT_FAILURE);
    }
    window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if (window == nullptr) {
        std::cout << "Window could not be created! SDL_Error[" << SDL_GetError() << "]" << std::endl;
        exit(EXIT_FAILURE);
    }

    gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if (gRenderer == nullptr) {
        std::cout << "Renderer could not be created! SDL Error" << SDL_GetError() << "]" << std::endl;
        exit(EXIT_FAILURE);
    }

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not initialize! SDL_image Error[" << IMG_GetError() << "]" << std::endl;
        exit(EXIT_FAILURE);
    }

    //Get window surface
    screenSurface = SDL_GetWindowSurface( window );

    //Fill the surface white
    SDL_FillRect( screenSurface, nullptr, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

    //Update the surface
    SDL_UpdateWindowSurface( window );

    std::string filename = FILEPATH + "/data/images/player.png";
    SDL_Surface* loadedSurface = SDLSurfaceFromFile(filename);

    //player_surface = IMG_Load(filename.c_str());
    if (!loadedSurface) {
        std::cout << ">>>>>>>>>>>> filed to load image[" << filename << "]" << std::endl;
    } else {
        std::cout << ">>>>>>>>>>>> filed [" << filename << "] loaded, w[" << loadedSurface->w << "], h[" << loadedSurface->h << "]" << std::endl;
        GameMediator::get_instance()->player_w = loadedSurface->w;
        GameMediator::get_instance()->player_h = loadedSurface->h;
        player_texture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if (player_texture == nullptr) {
            printf( "Unable to create texture from surface. SDL Error: %s\n", SDL_GetError() );
        }
        SDL_FreeSurface(loadedSurface);
    }

    // upperland logo
    upperland_texture = loadTexture( "/data/images/upperland_logo.png" );
    SDL_QueryTexture(upperland_texture, nullptr, nullptr, &upperland_logo_w, &upperland_logo_h);

    //tileset = loadTexture( "/data/images/tileset_brown.png" );
    tileset = loadTexture( "/data/images/tileset_green.png" );
    background = loadTexture( "/data/images/background.png");
    livestexture = loadTexture( "/data/images/1up.png" );
    bombstexture = loadTexture( "/data/images/bomb.png" );
    powertexture = loadTexture( "/data/images/power.png" );
    helicetexture = loadTexture( "/data/images/helice.png" );

    // calc item position in the HUD
    hud_total_w = SCREEN_WIDTH/2;
    hud_bar_w = hud_total_w/200;
    hud_bar_x = SCREEN_WIDTH/4;

    int item_space = MAX_ITEM_COUNT*HUD_ITEM_SIZE;
    int left_space = hud_total_w/2 - item_space - HUD_ITEM_SIZE*2;

    hud_item_spacer = left_space/MAX_ITEM_COUNT;
    std::cout << "hud_item_spacer[" << hud_item_spacer << "], hud_total_w[" << hud_total_w << "], item_space[" << item_space << "], left_space[" << left_space << "]" << std::endl;


    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    std::string music_filename = FILEPATH + "/data/sounds/hero_quest_ingame.mod";
    gMusic = Mix_LoadMUS(music_filename.c_str());
    if( gMusic == nullptr ) {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    Mix_PlayMusic( gMusic, -1 );
}

void graphlib::drawScreen()
{
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( gRenderer );
    copySDLPortion(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, background);


    if (GameMediator::get_instance()->map_list_map.at(GameMediator::get_instance()->currentStage).size() > 0) {
        for (int i=0; i<MAP_W; i++) {
            for (int j=0; j<MAP_H; j++) {
                int currentTileValue = GameMediator::get_instance()->map_list_map.at(GameMediator::get_instance()->currentStage).at(GameMediator::get_instance()->currentMap).tile[i][j];
                if (currentTileValue == 1) {
                    SDL_Rect fillRect = { i*TILESIZE, j*TILESIZE, TILESIZE, TILESIZE };
                    // 924910, a56022, b67932
                    if (j >= 6) {
                        SDL_SetRenderDrawColor( gRenderer, 0xB6, 0x79, 0x32, 0xFF );
                    } else if (j >= 3) {
                        SDL_SetRenderDrawColor( gRenderer, 0xA5, 0x60, 0x22, 0xFF );
                    } else {
                        SDL_SetRenderDrawColor( gRenderer, 0x92, 0x49, 0x10, 0xFF );
                    }
                    SDL_RenderFillRect( gRenderer, &fillRect );

                    if (j >= 6) {
                        copySDLPortion(0, 128, TILESIZE, TILESIZE, i*TILESIZE, j*TILESIZE, tileset);
                    } else if (j >= 3) {
                        copySDLPortion(0, 64, TILESIZE, TILESIZE, i*TILESIZE, j*TILESIZE, tileset);
                    } else {
                        copySDLPortion(0, 0, TILESIZE, TILESIZE, i*TILESIZE, j*TILESIZE, tileset);
                    }

                } else if (currentTileValue == 2) {
                    //std::cout << "TILE[" << i << "][" << j << "]: [" << currentTileValue << "]" << std::endl;
                    SDL_Rect fillRect = { i*TILESIZE, j*TILESIZE, TILESIZE, TILESIZE };
                    int r = 0xB5-lava_color_count;
                    if (r < 0) {
                        r = 0;
                    }
                    int g = 0x19-lava_color_count;
                    if (g < 0) {
                        g = 0;
                    }
                    int b = 0x19-lava_color_count;
                    if (b < 0) {
                        b = 0;
                    }
                    SDL_SetRenderDrawColor( gRenderer, r, g, b, 0xFF ); // b51919
                    if (lava_color_direction == false) {
                        lava_color_count++;
                        if (lava_color_count > 100) {
                            lava_color_direction = true;
                        }
                    } else {
                        lava_color_count--;
                        if (lava_color_count < 1) {
                            lava_color_direction = false;
                        }
                    }
                    SDL_RenderFillRect( gRenderer, &fillRect );
                }
            }
        }
    }

}

void graphlib::drawPlayer(double x, double y, e_DIRECTION direction, double playerAccel, double playerSpeed)
{
    //std::cout << "graphlib::drawPlayer - playerAccel[" << playerAccel << "], playerSpeed[" << playerSpeed << "]" << std::endl;
    if (direction == DIRECTION_LEFT) {
        copySDLPortion(0, GameMediator::get_instance()->player_h/2, GameMediator::get_instance()->player_w, GameMediator::get_instance()->player_h/2, x, y, player_texture);
        copySDLPortion(0, helice_frame*15, 32, 15, x+50, y+6, helicetexture);
    } else {
        copySDLPortion(0, 0, GameMediator::get_instance()->player_w, GameMediator::get_instance()->player_h/2, x, y, player_texture);
        copySDLPortion(0, helice_frame*15, 32, 15, x-6, y+6, helicetexture);
    }

    if (helice_frame_timer < tlib.getTimer()) {
        helice_frame++;
        if (helice_frame > 3) {
            helice_frame = 0;
        }
        if (playerAccel == 0.0) {
            helice_frame_timer = tlib.getTimer() + 260;
        } else {
            helice_frame_timer = tlib.getTimer() + 100-(playerSpeed*10);
        }
    }
}

void graphlib::drawHud(unsigned int lives, unsigned int bombs, unsigned int points, unsigned long timeTotal, unsigned long timeLeft)
{
    SDL_SetRenderDrawColor( gRenderer, 0x6A, 0x68, 0x6D, 0xFF ); // 6a686d
    SDL_Rect fillRect = { 0, VISIBLE_HEIGHT, SCREEN_WIDTH, HUD_HEIGHT };
    SDL_RenderFillRect( gRenderer, &fillRect );

    // power bar
    copySDLPortion(hud_bar_x-96, VISIBLE_HEIGHT+16, 76, 16, powertexture);
    unsigned long percentTime = (timeLeft*100)/timeTotal;
    SDL_SetRenderDrawColor( gRenderer, 0xEB, 0xEB, 0x6D, 0x49 ); // ebeb49
    for (int i=0; i<percentTime; i++) {
        SDL_Rect fillRect = { i*(hud_bar_w*2)+hud_bar_x, VISIBLE_HEIGHT+LAVA_AREA+16, hud_bar_w, 16 };
        SDL_RenderFillRect( gRenderer, &fillRect );
    }
    // TODO: calculate just once
    int logo_x = SCREEN_WIDTH/2 - upperland_logo_w/2;
    int logo_y = SCREEN_HEIGHT -4 - upperland_logo_h; // TODO: get logo-h
    copySDLPortion(logo_x, logo_y, upperland_logo_w, upperland_logo_h, upperland_texture);

    for (unsigned int i=0; i<lives; i++) {
        //int pos_x = hud_bar_x + (hud_total_w - (i+1)*(HUD_ITEM_SIZE+hud_item_spacer));
        int pos_x = hud_bar_x + i*(HUD_ITEM_SIZE+hud_item_spacer);
        //std::cout << "lives[" << lives << "], i[" << i << "], hud_total_w[" << hud_total_w << "], pos_x[" << pos_x << "], hud_item_spacer[" << hud_item_spacer << "]" << std::endl;
        copySDLPortion(pos_x, VISIBLE_HEIGHT+LAVA_AREA+48, HUD_ITEM_SIZE, HUD_ITEM_SIZE, livestexture);
    }

    for (unsigned int i=0; i<bombs; i++) {
        int pos_x = hud_bar_x + (hud_total_w - (i+1)*(HUD_ITEM_SIZE+hud_item_spacer)) - HUD_ITEM_SIZE*2;
        //std::cout << "bombs[" << bombs << "], i[" << i << "], hud_total_w[" << hud_total_w << "], pos_x[" << pos_x << "], hud_item_spacer[" << hud_item_spacer << "]" << std::endl;
        copySDLPortion(pos_x, VISIBLE_HEIGHT+LAVA_AREA+48, HUD_ITEM_SIZE, HUD_ITEM_SIZE, bombstexture);
    }
}

void graphlib::updateScreen()
{
    SDL_RenderPresent( gRenderer );
}

SDL_Texture *graphlib::loadTexture(std::string filename)
{
    //The final texture
    SDL_Texture* newTexture = nullptr;
    std::string path = FILEPATH + filename;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == nullptr )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == nullptr )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

void graphlib::quit()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(window);

    gRenderer = nullptr;
    window = nullptr;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Surface *graphlib::SDLSurfaceFromFile(std::string filename)
{
    SDL_RWops *rwop;
    SDL_Surface *spriteCopy;

    //filename = StringUtils::clean_filename(filename);
    rwop = SDL_RWFromFile(filename.c_str(), "rb");

    if (!rwop) {
        std::cout << "DEBUG.SDLSurfaceFromFile - Error in graphicsLib::SDLSurfaceFromFile - file '" << filename << "' not found\n";
            return NULL;
    }
    spriteCopy = IMG_Load_RW(rwop, 1);
    if (spriteCopy == NULL) {
        std::cout << "[graphicsLib::SDLSurfaceFromFile] Error on IMG_Load_RW, could not load image '" << filename << "'. Details: " << IMG_GetError() << std::endl;
    }
    if (screenSurface == NULL || screenSurface->format == NULL) {
        return NULL;
    }

    //SDL_Surface *res_surface = SDL_DisplayFormat(spriteCopy);
    //SDL_FreeSurface(spriteCopy);
    //SDL_SetColorKey(res_surface, SDL_SRCCOLORKEY, SDL_MapRGB(game_screen->format, COLORKEY_R, COLORKEY_G, COLORKEY_B));

    return spriteCopy;
}

void graphlib::copySDLPortion(int x, int y, int w, int h, SDL_Texture *gTexture)
{
    copySDLPortion(0, 0, w, h, x, y, gTexture);
}

void graphlib::copySDLPortion(int x, int y, int w, int h, int dest_x, int dest_y, SDL_Texture *gTexture)
{
    SDL_Rect src, dest;
    src.x = x;
    src.y = y;
    src.w = w;
    src.h = h;
    dest.x = dest_x;
    dest.y = dest_y;
    dest.w = w;
    dest.h = h;

    if (!gTexture) {
        std::cout << "copySDLArea - ERROR surfaceOrigin is NULL\n";
        return;
    }
    if (!gRenderer) {
        std::cout << "copySDLPortion - ERROR gRenderer is NULL - ignoring..." << std::endl;
        return;
    }
/*
    if (src.x >= w || (src.x+src.w) > w) {
        //printf(">> Invalid X portion src.x[%d], src.w[%d] for image.w[%d] <<\n", src.x, src.w, surfaceOrigin->w);
        fflush(stdout);
        return;
    }
    if (src.y >= h || (src.y+src.h) > h) {
        printf(">> Invalid Y portion[%d] h[%d] for image.w[%d] and image.h[%d] <<\n", src.y, src.h, w, h);
        fflush(stdout);
        return;
    }
*/
    SDL_RenderCopy( gRenderer, gTexture, &src, &dest );
}
