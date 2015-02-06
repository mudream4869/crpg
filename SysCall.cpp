#include <queue>
#include <chrono>
#include <thread>
#include "Event.h"
#include "SysCall.h"
#include "WindowBlockType.h"
#include "GlobalVariable.h"
#include "Env.h"

#include "SceneStart.h"
#include "ScenePlay.h"
#include "SceneSave.h"
#include "SceneLoad.h"
#include "SceneGameOver.h"

#include "GameObject.h"
#include "AudioSystem.h"
#include "Mask.h"

#include "Type.h"
#include "PyLock.h"
#include "ImgCtrl.h"

#include "WindowMsg.h"
#include "WindowInputNumber.h"
#include "WindowMsgSelect.h"

std::mutex Sys::syscall_mutex;

void Sys::InitSys(){
    return;
}

PyObject* Sys::SysCall(PyObject* self, PyObject* para){
    // TODO: garbage recycle
    fprintf(stderr, "SysCall========\n");
    //PyObject_Print(self, stderr, 0);
    //PyObject_Print(para, stderr, 0);
    PyObject* ret_value;
    //printf("SysCall\n");
    char cmd[20];
    strcpy(cmd, PyString_AsString(PyTuple_GetItem(para, 0)));
    // TODO:ENTERPRETER
    if(strcmp(cmd, "ShowMsg") == 0){
        fprintf(stderr, "Call ShowMsg\n");
        WindowBlockType::msg = new WindowMsg(PyString_AsString(PyTuple_GetItem(para, 1)));
        
        auto state = PyEval_SaveThread();
        PyUnlock();
        while(WindowBlockType::msg != nullptr); // TODO: change to cv
        PyLock();
        PyEval_RestoreThread(state);
        
        Py_INCREF(Py_None);
        ret_value = Py_None;
    }else if(strcmp(cmd, "ShowMsgSelect") == 0){
        PyObject* opt_list = PyTuple_GetItem(para, 1);
        int sz = PyList_Size(opt_list);
        char** options = new char*[sz];
        for(int lx = 0;lx < (int)PyList_Size(opt_list);lx++){
            char* tmp_str = PyString_AsString(PyList_GetItem(opt_list, lx));
            options[lx] = new char[strlen(tmp_str) + 2];
            strcpy(options[lx], tmp_str);
        }
        WindowBlockType::msg = new WindowMsgSelect(options, sz);

        auto state = PyEval_SaveThread();
        PyUnlock();
        while(WindowBlockType::msg != nullptr); // TODO: change to cv
        PyLock();
        PyEval_RestoreThread(state);

        ret_value = Py_BuildValue("i", WindowBlockType::ret_value.int_value);
    }else if(strcmp(cmd, "SetValue") == 0){
        fprintf(stderr, "Call SetValue\n");
        GlobalVariable::SetValue(
            PyString_AsString(PyTuple_GetItem(para, 1)),
            (int)PyInt_AsLong(PyTuple_GetItem(para, 2))
        );
        Py_INCREF(Py_None);
        ret_value = Py_None;

    }else if(strcmp(cmd, "GetValue") == 0){
        fprintf(stderr, "Call GetValue\n");
        int retvalue = GlobalVariable::GetValue(
            PyString_AsString(PyTuple_GetItem(para, 1))
        );
        ret_value = Py_BuildValue("i", retvalue);

    }else if(strcmp(cmd, "SetFlag") == 0){
        fprintf(stderr, "Call SetFlag\n");
        GlobalVariable::SetFlag(
            PyString_AsString(PyTuple_GetItem(para, 1)),
            PyObject_IsTrue((PyTuple_GetItem(para, 2)))
        );
        Py_INCREF(Py_None);
        ret_value = Py_None;

    }else if(strcmp(cmd, "GetFlag") == 0){
        fprintf(stderr, "Call GetFLag\n");
        int retvalue = GlobalVariable::GetFlag(
            PyString_AsString(PyTuple_GetItem(para, 1))
        );
        ret_value = Py_BuildValue("i", retvalue);

    }else if(strcmp(cmd, "DoMove") == 0){
        char active_event_name[20];
        strcpy(active_event_name, PyString_AsString(PyTuple_GetItem(para, 1)));
        PyObject* moving_list = PyTuple_GetItem(para, 2);
        std::queue<int> arg;
        for(int lx = 0;lx < (int)PyList_Size(moving_list);lx++){
            arg.push((int)PyInt_AsLong(PyList_GetItem(moving_list, lx)));
        }
        Event::event_pool[active_event_name]->SetMovement(arg);
        Py_INCREF(Py_None);
        ret_value = Py_None;

    }else if(strcmp(cmd, "ShowSaveFile") == 0){
        SceneSave::Call();
        // Wait for saving
        Py_INCREF(Py_None);
        ret_value = Py_None;

    }else if(strcmp(cmd, "WaitForMove") == 0){
        char active_event_name[20];
        strcpy(active_event_name, PyString_AsString(PyTuple_GetItem(para, 1)));
        Event* check_event = Event::event_pool[active_event_name];
        
        auto state = PyEval_SaveThread();
        PyUnlock();
        while(check_event->Moving()); // TODO: use condition var
        PyLock();
        PyEval_RestoreThread(state);
        
        Py_INCREF(Py_None);
        ret_value = Py_None;

    }else if(strcmp(cmd, "ChangeMap") == 0){
        char map_name[20];
        int start_x, start_y, dir;
        strcpy(map_name, PyString_AsString(PyTuple_GetItem(para, 1)));
        start_x = (int)(PyInt_AsLong(PyTuple_GetItem(para, 2)));
        start_y = (int)(PyInt_AsLong(PyTuple_GetItem(para, 3)));
        dir = (int)(PyInt_AsLong(PyTuple_GetItem(para, 4)));
        /*if(env->count("scene_play") == 0){
            fprintf(stderr, "akjsfhkaj\n");
        }*/
        ScenePlay::scene_play->ChangeMap(Map::map_pool[map_name], start_x, start_y, dir);
        Py_INCREF(Py_None);
        ret_value = Py_None;
    
    }else if(strcmp(cmd, "SetGameObject") == 0){
        fprintf(stderr, "call SetGameObject");
        GameObjectData::SetGameObjectCount(
            PyString_AsString(PyTuple_GetItem(para, 1)),
            PyLong_AsLong((PyTuple_GetItem(para, 2)))
        );
        Py_INCREF(Py_None);
        ret_value = Py_None;

    }else if(strcmp(cmd, "GetGameObject") == 0){
        int retvalue = GameObjectData::GetGameObjectCount(
            PyString_AsString(PyTuple_GetItem(para, 1))
        );
        ret_value = Py_BuildValue("i", retvalue);

    }else if(strcmp(cmd, "PlaySE") == 0){
        AudioSystem::PlaySE(PyString_AsString(PyTuple_GetItem(para, 1)));
        Py_INCREF(Py_None);
        ret_value = Py_None;

    }else if(strcmp(cmd, "PlayBGM") == 0){
        AudioSystem::PlayBGM(PyString_AsString(PyTuple_GetItem(para, 1)));
        Py_INCREF(Py_None);
        ret_value = Py_None;
    
    }else if(strcmp(cmd, "SetMask") == 0){
        fprintf(stderr, "Call Set Mask\n");
        PyObject* col1 = PyTuple_GetItem(para, 1);
        PyObject* col2 = PyTuple_GetItem(para, 2);

        int ms = (int)PyLong_AsLong(PyTuple_GetItem(para, 3));
        Color4f st_color, ed_color;
        
        st_color.r = PyLong_AsLong((PyTuple_GetItem(col1, 0)))/(float)255;
        st_color.g = PyLong_AsLong((PyTuple_GetItem(col1, 1)))/(float)255;
        st_color.b = PyLong_AsLong((PyTuple_GetItem(col1, 2)))/(float)255;
        st_color.a = PyLong_AsLong((PyTuple_GetItem(col1, 3)))/(float)255;
        
        ed_color.r = PyLong_AsLong((PyTuple_GetItem(col2, 0)))/(float)255;
        ed_color.g = PyLong_AsLong((PyTuple_GetItem(col2, 1)))/(float)255;
        ed_color.b = PyLong_AsLong((PyTuple_GetItem(col2, 2)))/(float)255;
        ed_color.a = PyLong_AsLong((PyTuple_GetItem(col2, 3)))/(float)255;
        
        Mask::SetMask(st_color, ed_color, ms);
        
        Py_INCREF(Py_None);
        ret_value = Py_None;
    }else if(strcmp(cmd, "Sleep") == 0){
        int ms = (int)PyLong_AsLong(PyTuple_GetItem(para, 1));
        std::chrono::milliseconds dura(ms);
        
        auto state = PyEval_SaveThread();
        PyUnlock();
        std::this_thread::sleep_for(dura);
        PyLock();
        PyEval_RestoreThread(state);
        
        Py_INCREF(Py_None);
        ret_value = Py_None;
    }else if(strcmp(cmd, "ShowImg") == 0){
        int index = (int)PyLong_AsLong(PyTuple_GetItem(para, 1));
        char img_fn[20]; strcpy(img_fn, PyString_AsString(PyTuple_GetItem(para, 2)));
        PyObject* p_pos = PyTuple_GetItem(para, 3);
        PyObject* p_rect = PyTuple_GetItem(para, 4);
        Vec2f pos = {
                (float)PyFloat_AsDouble(PyTuple_GetItem(p_pos, 0)),
                (float)PyFloat_AsDouble(PyTuple_GetItem(p_pos, 1))
            }, rect = {
                (float)PyFloat_AsDouble(PyTuple_GetItem(p_rect, 0)),
                (float)PyFloat_AsDouble(PyTuple_GetItem(p_rect, 1))
            };
        ImgCtrl::ShowImg(index, img_fn, pos, rect);
        
        Py_INCREF(Py_None);
        ret_value = Py_None;
    }else if(strcmp(cmd, "KillImg") == 0){
        fprintf(stderr, "call kill img");
        int index = (int)PyLong_AsLong(PyTuple_GetItem(para, 1));
        ImgCtrl::KillImg(index);

        Py_INCREF(Py_None);
        ret_value = Py_None;
    
    }else if(strcmp(cmd, "GameOver") == 0){
        fprintf(stderr, "game over\n"); 
        SceneGameOver::Call(); 
        Py_INCREF(Py_None);
        ret_value = Py_None;
    }else if(strcmp(cmd, "ReturnStart") == 0){
        SceneStart::Call();
        Py_INCREF(Py_None);
        ret_value = Py_None;

    }else if(strcmp(cmd, "ShowInputNumber") == 0){
        fprintf(stderr, "Show Inut Number");
        WindowBlockType::msg = new WindowInputNumber();
        auto state = PyEval_SaveThread();
        PyUnlock();
        while(WindowBlockType::msg != nullptr); // TODO: change to cv
        PyLock();
        PyEval_RestoreThread(state);
        
        fprintf(stderr, "%d\n", WindowBlockType::ret_value.int_value); 
        ret_value = Py_BuildValue("i", WindowBlockType::ret_value.int_value);
    
    }else{
        Py_INCREF(Py_None);
        ret_value = Py_None;
    
    }

    return ret_value;
}
