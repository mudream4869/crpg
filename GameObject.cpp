#include <cstdio>
#include <cstdlib>
#include "GameObject.h"

std::map<const char*, GameObjectData::GameObject*, StrCompare> GameObjectData::gameobject_pool;
std::map<const char*, int, StrCompare> GameObjectData::gameobject_count;

void GameObjectData::InitGameObject(){
    FILE* finit = fopen("objects/__init__.ini", "r") ;
    char name[20];
    while(fscanf(finit, "%s", name) != EOF){
        
    }
    return;
}

int GameObjectData::GetGameObjectCount(const char* str){
    if(gameobject_count.count(str) == 0)
        return 0;
    return gameobject_count[str];
}

Image* GameObjectData::GetGameObjectImage(const char* str){
    if(gameobject_pool.count(str) == 0)
        return nullptr;
    return gameobject_pool[str]->img;
}

void GameObjectData::CallGameObject(const char* str){
    if(gameobject_pool.count(str) == 0)
        return;
    
    PyObject* pArg = Py_BuildValue("()");
    PyObject* ret = PyObject_CallObject(gameobject_pool[str]->choose_callback, pArg);
    return;
}

void GameObjectData::SetGameObjectCount(const char* str, int val){
    if(gameobject_count.count(str) == 0){
        char* tmp = new char[strlen(str) + 2];
        strcpy(tmp, str);
        gameobject_count[tmp] = 0;
    }
    gameobject_count[str] = val;
    return;
}
