#ifndef CONFIG_DEF
#define CONFIG_DEF

#include "Type.h"

namespace Config{
    const char PATH_SAVEFILE[] = "saves/";
    const char PATH_MAPFILE[] =  "maps/";
    const float WINDOW_WIDTH = 2;
    const float WINDOW_HEIGHT = 2;

    extern char SCRIPT_PATH[20];
    extern char SCENESTART_IMG_NAME[20];
    extern char SCENESTART_BGM_NAME[20];
    extern char GAME_TITLE[20];
    extern char GAME_START_MAP_NAME[20];
    extern char HERO_IMG_NAME[20];
    extern Vec2i GAME_START_POS;
    extern char GAME_START_DIR[20];
    
    void InitConfig();


};

const char CONFIG_PATH_SAVEFILE[] = "saves/";

const int CONFIG_DIR_X[] = {0, -1, 1, 0};
const int CONFIG_DIR_Y[] = {1, 0, 0, -1};

const float CONFIG_DELTA_X = 0.2;
const float CONFIG_DELTA_Y = 0.2;

#endif
