#include "inc_py.h"

#include <cstdio>
#include <cstdlib>
#include <thread>

#include "GameObject.h"

#include "Script.h"

std::map<const char*, GameObjectData::GameObject, StrComp> GameObjectData::gameobject_pool;
std::map<const char*, int, StrComp> GameObjectData::gameobject_count;

void GameObjectData::InitGameObject(){
    PyObject* p_module = PyImport_ImportModule("scripts.objects");
    
    if(p_module == NULL){

#ifdef DEBUG
        fprintf(stderr, "Fail to load scripts.objects\n");
        PyErr_Print();
        fprintf(stderr, "[Warning] no gameobject initial.\n");
#endif

        return;
    }

    FILE* finit = fopen("objects/__init__.ini", "r") ;
    if(finit == NULL){

#ifdef DEBUG
        fprintf(stderr, "GameObjectData: Fail to open objects/__init__.ini");
        fprintf(stderr, "[Warning] no gameobject initial.\n");
#endif

        return;
    }

    char name[20], image_name[20], script_name[20];
    while(fscanf(finit, "%s %s %s", name, image_name, script_name) != EOF){
        char full_img_path[20];
        sprintf(full_img_path, "objects/%s", image_name);
        
        GameObject new_obj;
        strcpy(new_obj.name, name);
        new_obj.img = new Image(full_img_path);
        new_obj.script = new Script(p_module, script_name);
        
        char* name_tmp = new char[strlen(name) + 2];
        strcpy(name_tmp, name);
        gameobject_pool[name_tmp] = new_obj;
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
    return gameobject_pool[str].img;
}

void GameObjectData::CallGameObject(const char* str){
    if(gameobject_pool.count(str) == 0)
        return;
    gameobject_pool[str].script->Shell();
    return;
}

void GameObjectData::SetGameObjectCount(const char* str, int val){
    if(val == 0){
        gameobject_count.erase(str);
        return;
    }
    if(gameobject_count.count(str) == 0){
        char* tmp = new char[strlen(str) + 2];
        strcpy(tmp, str);
        gameobject_count[tmp] = 0;
    }
    gameobject_count[str] = val;
    return;
}
