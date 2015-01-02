#include <cstring>
#include <cstdlib>
#include "Env.h"
#include "Scene.h"
#include "SysCall.h"

Env* env;

void EnvInit(){
    env = new Env;
    return;
}

void EnvInsert(const char* str, void* inp){
    char* ss = new char[strlen(str) + 2];
    strcpy(ss, str);
    env->operator[](ss) = inp;
    return;
}

void* EnvGet(const char* str){
    return env->operator[](str);
}

int EnvCount(const char* str){
    return env->count(str);
}

std::map<const char*, Event*, StrCompare>* EnvGetEventPool(){
    return (std::map<const char*, Event*, StrCompare>*)(EnvGet("event_pool")) ;
}

std::map<const char*, Map*, StrCompare>* EnvGetMapPool(){
    return (std::map<const char*, Map*, StrCompare>*)(EnvGet("map_pool"));
}

Event* EnvGetEvent(const char* event_file){
    std::map<const char*, Event*, StrCompare>& get = *EnvGetEventPool();
    if(get.count(event_file))
        return get[event_file];
    else
        return nullptr;
}

Map* EnvGetMap(const char* map_name){
    std::map<const char*, Map*, StrCompare>& get = *EnvGetMapPool();
    if(get.count(map_name))
        return get[map_name];
    else
        return nullptr;
}

void EnvSetCertainScene(const char* scene_name){
    Scene** now_scene = (Scene**) EnvGet("scene_certain");
    (*now_scene) = *((Scene**) EnvGet(scene_name));
    return;
}

void EnvAddMap(const char* map_name, Map* map_pointer){
    std::map<const char*, Map*, StrCompare>& get = *EnvGetMapPool();
    char* new_str = new char[strlen(map_name) + 2];
    strcpy(new_str, map_name);
    get[new_str] = map_pointer;
    return;
}
