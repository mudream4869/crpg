#ifndef GAMEOBJECTDATA_DEF
#define GAMEOBJECTDATA_DEF

#include "inc_py.h"
#include <map>
#include "Image.h"
#include "Tool.h"

namespace GameObjectData{
    struct GameObject{
        Image* img;
        char name[20];
        PyObject* choose_callback;
    };
    extern std::map<const char*, GameObject, StrComp> gameobject_pool;
    extern std::map<const char*, int, StrComp> gameobject_count;
    
    void InitGameObject();

    int GetGameObjectCount(const char* str);
    Image* GetGameObjectImage(const char* str);
    void CallGameObject(const char* str); 
    void SetGameObjectCount(const char* str, int val);
};

#endif
