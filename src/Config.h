#ifndef CONFIG_DEF
#define CONFIG_DEF

#include "Type.h"

namespace Config{

    /**
     *  @brief path of each resource
     */
    const char PATH_SAVEFILE[] = "saves";
    const char PATH_MAPFILE[] =  "maps";
    const char PATH_FONTFILE[] = "fonts";
    const char PATH_OBJECTFILE[] = "objects";
    const char PATH_CONFIGFILE[] = "configs";
    const char PATH_TEXTUREFILE[] = "textures";
    const char PATH_PICTUREFILE[] = "pictures";
    const char PATH_SOUND_SEFILE[] = "sounds/SE";
    const char PATH_SOUND_BGMFILE[] = "sounds/BGM";

    extern char SCRIPT_PATH[20];
    extern char SCENESTART_IMG_NAME[20];
    extern char SCENESTART_BGM_NAME[20];
    extern char GAME_TITLE[20];
    extern char GAME_START_MAP_NAME[20];
    extern char HERO_IMG_NAME[20];
    extern Vec2i GAME_START_POS;
    extern char GAME_START_DIR[20];
    
    /**
     *  @brief Read Config from setting file
     */
    void InitConfig();
};



#endif
