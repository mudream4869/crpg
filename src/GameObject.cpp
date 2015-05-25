#include "inc_py.h"

#include <cstdio>
#include <cstdlib>
#include <thread>
#include <map>

#include "GameObject.h"
#include "Script.h"
#include "Config.h"
#include "Tool.h"

#include "debugger/debugger.h"

using std::vector;
using std::string;
using std::pair;

struct GameObject{
    Image* img;
    char name[20];
    Script* script;
};

static std::map<string, GameObject> gameobject_pool;
static std::map<string, int> gameobject_count;

void GameObjectData::InitGameObject(){
    PyObject* p_module = PyImport_ImportModule("scripts.objects");
    
    if(p_module == NULL){
        Debugger::Print("Fail to load scripts.objects\n");
        Debugger::PrintPyErr();
        Debugger::Print("[Warning] no gameobject initial.\n");
        return;
    }

    FILE* finit = fopen("objects/__init__.ini", "r") ;
    if(finit == NULL){
        Debugger::Print("GameObjectData: Fail to open objects/__init__.ini\n");
        Debugger::Print("[Warning] no gameobject initial.\n");
        return;
    }
    
    /** Read in gameobject */
    char name[20], image_name[20], script_name[20];
    while(fscanf(finit, "%s %s %s", name, image_name, script_name) != EOF){
        char full_img_path[20];
        sprintf(full_img_path, "%s/%s", Config::PATH_OBJECTFILE, image_name);
        
        GameObject new_obj;
        strcpy(new_obj.name, name);
        new_obj.img = new Image(full_img_path);
        new_obj.script = new Script(p_module, script_name);
        
        gameobject_pool[string(name)] = new_obj;
    }
    fclose(finit);
    return;
}

int GameObjectData::GetGameObjectCount(string str){
    if(gameobject_count.count(str) == 0)
        return 0;
    return gameobject_count[str];
}

Image* GameObjectData::GetGameObjectImage(string str){
    if(gameobject_pool.count(str) == 0)
        return nullptr;
    return gameobject_pool[str].img;
}

void GameObjectData::CallGameObject(string str){
    if(gameobject_pool.count(str) == 0)
        return;
    gameobject_pool[str].script->Shell();
    return;
}

void GameObjectData::SetGameObjectCount(string str, int val){
    
    /** Let 0 amount gameobject display from list*/
    if(val == 0){
        gameobject_count.erase(str);
        return;
    }

    if(gameobject_count.count(str) == 0)
        gameobject_count[str] = 0;
    
    gameobject_count[str] = val;
    return;
}

vector< pair<string, int> > GameObjectData::DumpCounts(){
    vector< pair<string,int> > ret;
    for(auto& it : gameobject_count)
        ret.push_back(pair<string, int>(it.first, it.second));
    return ret;
}

int GameObjectData::GetSize(){
    return gameobject_count.size();
}

void GameObjectData::ClearGameObject(){
    gameobject_count.clear();
    return;
}
