#ifndef GAMEOBJECTDATA_DEF
#define GAMEOBJECTDATA_DEF

#include <vector>
#include <utility>
#include <string>

#include "Image.h"

namespace GameObjectData{
    void InitGameObject();
    int GetGameObjectCount(const char* str);
    Image* GetGameObjectImage(const char* str);
    void CallGameObject(const char* str); 
    void SetGameObjectCount(const char* str, int val);
    
    int GetSize();
     
    std::vector< std::pair< std::string, int> > DumpCounts();
};

#endif
