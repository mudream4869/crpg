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
#include "AudioSystem.h"

Image* img1;

Scene* now_scene;
Scene* start_scene;
Scene* play_scene;
Scene* save_scene;
Scene* load_scene;

Tile* hero_tile;
Hero* hero;


void LoadMaps();
void LoadConfig();

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
    
    std::atexit(AudioSystem::ExitAudioSystem);
    AudioSystem::InitAudioSystem();

    img1 = new Image("textures/hero.bmp");
    hero = new Hero();
    hero_tile = new Tile();
    hero_tile->SetImage(img1);
    hero_tile->SetSize(32, 48);
    hero->SetTile(hero_tile);
    hero->SetWalkPiece();
    
    LoadMaps();
    LoadConfig();

    start_scene = new SceneStart();
    save_scene = new SceneSave();
    load_scene = new SceneLoad();

    now_scene = start_scene;
 
    fprintf(stderr, "Scene set up.\n");

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

void LoadMaps(){
    FILE* fp = fopen("maps/__init__.ini", "r") ;
    if(fp == NULL){
        fprintf(stderr, "Error : Not found maps/__init__.ini\n");
        exit(1);
    }
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
    fclose(fp);
    return;
}

void LoadConfig(){
    FILE* fp = fopen("configs/init.ini", "r");
    if(fp == NULL){
        fprintf(stderr, "Error : Not found configs/init.ini\n");
        exit(1);
    }
    char line[100];
    char startmap_name[20];
    Vec2i startpos;
    while(fscanf(fp, "%s", line) != EOF){
        int eq_ptr = -1;
        for(int lx = 0;line[lx] != 0;lx++)
            if(line[lx] == '=')
                eq_ptr = lx;
        if(eq_ptr == -1) // Not setting
            continue;
        line[eq_ptr] = 0;
        if(strcmp(line, "startmap") == 0){
            strcpy(startmap_name, line+eq_ptr+1);
        }else if(strcmp(line, "startpos") == 0){
            startpos = Str2Vec2i(line+eq_ptr+1);
        }
    }
    play_scene = new ScenePlay(EnvGetMap(startmap_name), hero, startpos.x, startpos.y);
    return;
}
