#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "Type.h"
#include "Config.h"

#include "debugger/debugger.h"

char Config::SCENESTART_IMG_NAME[20];
char Config::SCENESTART_BGM_NAME[20];
char Config::GAME_START_MAP_NAME[20];
char Config::SCRIPT_PATH[] = ".";
char Config::HERO_IMG_NAME[20];
char Config::GAME_START_DIR[20];

Vec2i Config::GAME_START_POS;
char Config::GAME_TITLE[20];

void Config::InitConfig(){
    char fn[40];
    sprintf(fn, "%s/init.ini", Config::PATH_CONFIGFILE);
    
    FILE* fp = fopen(fn, "r");
    if(fp == NULL){
        fprintf(stderr, "Error : Not found %s\n", fn);
        exit(1);
    }
    char line[100];
    while(fscanf(fp, "%s", line) != EOF){
        int eq_ptr = -1;
        for(int lx = 0;line[lx] != 0;lx++)
            if(line[lx] == '=')
                eq_ptr = lx;
        if(eq_ptr == -1) // Not setting
            continue;
        line[eq_ptr] = 0;
        if(strcmp(line, "startmap") == 0){
            strcpy(GAME_START_MAP_NAME, line+eq_ptr+1);
        }else if(strcmp(line, "startpos") == 0){
            GAME_START_POS = Str2Vec2i(line+eq_ptr+1);
        }else if(strcmp(line, "startimg") == 0){
            sprintf(SCENESTART_IMG_NAME, "pictures/%s", line+eq_ptr+1);
        }else if(strcmp(line, "startbgm") == 0){
            // 圖片和音樂載入機制不同
            sprintf(SCENESTART_BGM_NAME, "%s", line+eq_ptr+1);
        }else if(strcmp(line, "gametitle") == 0){
            strcpy(GAME_TITLE, line+eq_ptr+1);
        }else if(strcmp(line, "heroimg") == 0){
            strcpy(HERO_IMG_NAME, line+eq_ptr+1);
        }else if(strcmp(line, "startdir") == 0){
            strcpy(GAME_START_DIR, line+eq_ptr+1);
        }else{
            Debugger::Print("Config: [Warning] unknow setting name: %s\n", line);
        }
    }
    fclose(fp);
    return;
}
