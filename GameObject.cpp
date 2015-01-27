#include <cstdio>
#include <cstdlib>
#include <thread>

#include "GameObject.h"
#include "SysCall.h"
#include "PyLock.h"

std::map<const char*, GameObjectData::GameObject, StrCompare> GameObjectData::gameobject_pool;
std::map<const char*, int, StrCompare> GameObjectData::gameobject_count;

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
        Image* new_img = new Image(full_img_path);
        
        PyObject* p_class = PyObject_GetAttrString(p_module, script_name);

#ifdef DEBUG
        if(p_class == NULL){
            fprintf(stderr, "Fail load 'class' %s from objects\n", script_name);
            PyErr_Print();
            exit(1);
        } 
#endif

        PyMethodDef *callback = new PyMethodDef;

        callback->ml_name = "func";
        callback->ml_meth = Sys::SysCall;
        callback->ml_flags = 1;

        PyObject* pcb = PyCFunction_New(callback, NULL);
        PyObject* pArg = Py_BuildValue("(O)", pcb);

        PyObject* p_inst = PyObject_CallObject(p_class, pArg);

#ifdef DEBUG
        if(p_inst == NULL){
            fprintf(stderr, "Fail to get instance of gameobject %s\n", script_name);
            PyErr_Print();
            exit(1);
        }
#endif

        PyObject* p_func = PyObject_GetAttrString(p_inst, "Action");

#ifdef DEBUG
        if(p_inst == NULL){
            fprintf(stderr, "Fail to get gameobject %s 's Action function.\n", script_name);
            PyErr_Print();
            exit(1);
        }
#endif

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
    
    auto cb = gameobject_pool[str].choose_callback;
    std::thread torun(
        [cb]{
            PyLock();
            auto state = Py_NewInterpreter(); 
            PyEval_RestoreThread(state);
            PyObject* pArg = Py_BuildValue("()");

#ifdef DEBUG
            PyErr_Clear();
#endif

            PyObject* ret = PyObject_CallObject(cb, pArg);

#ifdef DEBUG
            if(PyErr_Occurred() != NULL){
                fprintf(stderr, "gameobject script error\n");
                PyErr_Print();
                exit(1);
            }
#endif

            Py_XDECREF(pArg);
            Py_XDECREF(ret);
            PyUnlock();
        }
    );
    torun.detach();
 
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
