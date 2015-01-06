#ifndef GAMEOBJECTDATA_DEF
#define GAMEOBJECTDATA_DEF

#include "Env.h"
#include "Image.h"
#include "Python/Python.h"

namespace GameObjectData{
    struct GameObject{
        Image* img;
        char name[20];
        PyObject* choose_callback;
    };
    extern std::map<const char*, GameObject*, StrCompare> gameobject_pool;
    extern std::map<const char*, int, StrCompare> gameobject_count;
    
    void InitGameObject();

    int GetGameObjectCount(const char* str);
    Image* GetGameObjectImage(const char* str);
    void CallGameObject(const char* str); 
    void SetGameObjectCount(const char* str, int val);
};

#endif
