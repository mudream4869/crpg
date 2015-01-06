#include <cstdio>
#include <cstdlib>
#include "GameObject.h"
#include "SysCall.h"

std::map<const char*, GameObjectData::GameObject, StrCompare> GameObjectData::gameobject_pool;
std::map<const char*, int, StrCompare> GameObjectData::gameobject_count;

void GameObjectData::InitGameObject(){
    PyObject* p_module = PyImport_ImportModule("scripts.objects");
    FILE* finit = fopen("objects/__init__.ini", "r") ;
    char name[20], image_name[20], script_name[20];
    while(fscanf(finit, "%s %s %s", name, image_name, script_name) != EOF){
        char full_img_path[20];
        sprintf(full_img_path, "objects/%s", image_name);
        Image* new_img = new Image(full_img_path);
        
        PyObject* p_class = PyObject_GetAttrString(p_module, script_name);

        PyMethodDef *callback = new PyMethodDef;

        callback->ml_name = "func";
        callback->ml_meth = Sys::SysCall;
        callback->ml_flags = 1;

        PyObject* pcb = PyCFunction_New(callback, NULL);
        PyObject* pArg = Py_BuildValue("(O)", pcb);

        PyObject* p_inst = PyObject_CallObject(p_class, pArg);
        //TODO: kill pArg;
        PyObject* p_func = PyObject_GetAttrString(p_inst, "Action");

        GameObject new_obj;
        strcpy(new_obj.name, name);
        new_obj.img = new_img;
        new_obj.choose_callback = p_func;
        
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
    
    PyObject* pArg = Py_BuildValue("()");
    PyObject* ret = PyObject_CallObject(gameobject_pool[str].choose_callback, pArg);
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
