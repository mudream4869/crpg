#ifndef GAMEOBJECTDATA_DEF
#define GAMEOBJECTDATA_DEF

#include <vector>
#include <utility>
#include <string>

#include "Image.h"

using std::vector;
using std::string;
using std::pair;

namespace GameObjectData{
    void InitGameObject();
    int GetGameObjectCount(const char* str);
    Image* GetGameObjectImage(const char* str);
    void CallGameObject(const char* str); 
    void SetGameObjectCount(const char* str, int val);
    
    int GetSize();
     
    vector< pair<string, int> > DumpCounts();
};

#endif
