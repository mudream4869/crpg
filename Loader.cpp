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

#include "Window.h"
#include "WindowMsg.h"

#include "Env.h"

#include "Event.h"

// INSTANCE
#include "SysCall.h"
#include "Msg.h"
#include "GlobalVariable.h"
#include "GameObject.h"

Image* img1;

Scene* now_scene;
Scene* start_scene;
Scene* play_scene;
Scene* save_scene;
Scene* load_scene;

Tile* hero_tile;
Hero* hero;
Window* wintest;

// TODO: make initializer header and cpp
void InitResource(){
    Py_Initialize();
    PySys_SetPath(".");
    EnvInit();
 
    EnvInsert("event_pool", (void*)(new std::map<const char*, Event*, StrCompare>));
    EnvInsert("map_pool", (void*)(new std::map<const char*, Map*, StrCompare>));
    
    Sys::InitSys();
    Msg::InitMsg();
    GlobalVariable::InitGlobalVariable();
    GameObjectData::InitGameObject();

    img1 = new Image("hero.bmp");
    hero = new Hero();
    hero_tile = new Tile();
    hero_tile->SetImage(img1);
    hero_tile->SetSize(32, 48);
    hero->SetTile(hero_tile);
    hero->SetWalkPiece();

     // Load Maps
    FILE* fp = fopen("maps/__init__.ini", "r") ;
    char map_name[20];
    while(fscanf(fp, "%s", map_name) != EOF){
        char full_map_name[20];
        Map* read_map;
        sprintf(full_map_name, "maps/%s", map_name);
        read_map = new Map();
        read_map->LoadMap(full_map_name);
        // [File].tmx -> [File]
        map_name[strlen(map_name) - 4] = 0;
        read_map->SetName(map_name);
        fprintf(stderr, "add map %s\n", map_name);
        EnvAddMap(map_name, read_map);
    }

    play_scene = new ScenePlay(EnvGetMap("map1"), hero, 5, 5, 2, 2);
    start_scene = new SceneStart(2, 2);
    save_scene = new SceneSave();
    load_scene = new SceneLoad();

    now_scene = start_scene;
 
    fprintf(stderr, "Scene set up.\n");

    wintest = new WindowMsg(0.1, 0.1, 1.8, 1.8, "kajsdks");

    // Load Scenes
    EnvInsert("scene_certain", (void*)(&now_scene));
    EnvInsert("scene_play", (void*)(&play_scene));
    EnvInsert("scene_start", (void*)(&start_scene));
    EnvInsert("scene_save", (void*)(&save_scene));
    EnvInsert("scene_load", (void*)(&load_scene));

    // Load Maps

    printf("Init ok.\n");

    return;
}
