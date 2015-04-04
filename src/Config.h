#ifndef CONFIG_DEF
#define CONFIG_DEF

#include "Type.h"

namespace Config{
    const char PATH_SAVEFILE[] = "saves/";
    const char PATH_MAPFILE[] =  "maps/";

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



#endif
