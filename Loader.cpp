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

#include "Env.h"

#include "Event.h"

// INSTANCE
#include "SysCall.h"
#include "GlobalVariable.h"
#include "GameObject.h"
#include "AudioSystem.h"
#include "Mask.h"
#include "ImgCtrl.h"

#include "Config.h"

void LoadMaps();
void LoadConfig();

void InitResource(){
    Py_Initialize();
    //PyEval_InitThreads();
    //PyEval_ReleaseLock();
    PySys_SetPath(".");
    EnvInit();
 
    EnvInsert("event_pool", (void*)(new std::map<const char*, Event*, StrCompare>));
    EnvInsert("map_pool", (void*)(new std::map<const char*, Map*, StrCompare>));
    
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

    fprintf(stderr, "load scenes ok\n");
    // Load Maps
    printf("Init ok.\n");

    return;
}

void LoadMaps(){
    FILE* fp = fopen("maps/__init__.ini", "r") ;
    if(fp == NULL){
        fprintf(stderr, "Error : Not found maps/__init__.ini\n");
        exit(1);
    }
    char map_name[20];
    while(fscanf(fp, "%s", map_name) != EOF){
        char full_map_name[20];
        sprintf(full_map_name, "maps/%s", map_name);
        new Map(map_name);
        fprintf(stderr, "add map %s\n", map_name);
    }
    fclose(fp);
    return;
}
