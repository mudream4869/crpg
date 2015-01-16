#ifndef CONFIG_DEF
#define CONFIG_DEF

namespace Config{
    const char PATH_SAVEFILE[] = "saves/";
    const float WINDOW_WIDTH = 2;
    const float WINDOW_HEIGHT = 2;
    extern char SCENESTART_IMG_NAME[20];
    extern char SCENESTART_BGM_NAME[20];
};

const char CONFIG_PATH_SAVEFILE[] = "saves/";

const int CONFIG_DIR_X[] = {0, -1, 1, 0};
const int CONFIG_DIR_Y[] = {1, 0, 0, -1};

const float CONFIG_DELTA_X = 0.2;
const float CONFIG_DELTA_Y = 0.2;

#endif
