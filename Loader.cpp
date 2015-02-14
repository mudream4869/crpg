#include <cstdlib>

#include "Tool.h"

#include "Image.h"
#include "Tile.h"
#include "Map.h"
#include "Hero.h"

#include "Scene.h"
#include "ScenePlay.h"
#include "SceneStart.h"
#include "SceneSave.h"
#include "SceneLoad.h"
#include "SceneGameOver.h"

#include "Window.h"
#include "WindowBlockType.h"

#include "Event.h"

// INSTANCE
#include "SysCall.h"
#include "GlobalVariable.h"
#include "GameObject.h"
#include "AudioSystem.h"
#include "Mask.h"
#include "ImgCtrl.h"

#include "Config.h"
#include "Tool.h"

void LoadMaps();

void InitResource(){
    Py_Initialize();
    PySys_SetPath(".");
    
    Sys::InitSys();

    GlobalVariable::InitGlobalVariable();
    GameObjectData::InitGameObject();
    Mask::InitMask();
    ImgCtrl::InitImgCtrl();
     
    std::atexit(AudioSystem::ExitAudioSystem);
    AudioSystem::InitAudioSystem();

    LoadMaps();
    
    fprintf(stderr, "Ready to load scenes\n");

    Scene::scene_certain = new SceneStart();
    new ScenePlay();
    new SceneSave();
    new SceneLoad();
    new SceneGameOver();

    // Load Maps
    printf("Init ok.\n");

    return;
}

void LoadMaps(){
    std::vector<std::string> get_file_list = GetFileUnderDir("maps");
    for(int lx = 0;lx < get_file_list.size();lx++){
        char map_name[20];
        strcpy(map_name, get_file_list[lx].c_str());
        if(strcmp(GetFileNameExt(map_name), "tmx") != 0) continue;
        char full_map_name[20];
        sprintf(full_map_name, "maps/%s", map_name);
        new Map(map_name);
        fprintf(stderr, "add map %s\n", map_name);
    }
    return;
}
