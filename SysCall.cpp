#include <queue>
#include "Event.h"
#include "SysCall.h"
#include "Msg.h"
#include "GlobalVariable.h"
#include "Env.h"
#include "ScenePlay.h"

void Sys::InitSys(){
    return;
}

PyObject* Sys::SysCall(PyObject* self, PyObject* para){
    // TODO: garbage recycle
    fprintf(stderr, "SysCall========\n");
    PyObject_Print(self, stderr, 0);
    PyObject_Print(para, stderr, 0);
    //printf("SysCall\n");
    char cmd[20];
    strcpy(cmd, PyString_AsString(PyTuple_GetItem(para, 0)));
    // TODO:ENTERPRETER
    if(strcmp(cmd, "ShowMsg") == 0){
        fprintf(stderr, "Call ShowMsg\n");
        Msg::StartMsg(PyString_AsString(PyTuple_GetItem(para, 1)));
        while(Msg::IsMsgShow());
        Py_INCREF(Py_None);
        return Py_None;

    }else if(strcmp(cmd, "SetValue") == 0){
        fprintf(stderr, "Call SetValue\n");
        GlobalVariable::SetValue(
            PyString_AsString(PyTuple_GetItem(para, 1)),
            (int)PyInt_AsLong(PyTuple_GetItem(para, 2))
        );
        Py_INCREF(Py_None);
        return Py_None;

    }else if(strcmp(cmd, "GetValue") == 0){
        fprintf(stderr, "Call GetValue\n");
        int retvalue = GlobalVariable::GetValue(
            PyString_AsString(PyTuple_GetItem(para, 1))
        );
        return Py_BuildValue("i", retvalue);

    }else if(strcmp(cmd, "SetFlag") == 0){
        fprintf(stderr, "Call SetFlag\n");
        GlobalVariable::SetFlag(
            PyString_AsString(PyTuple_GetItem(para, 1)),
            PyObject_IsTrue((PyTuple_GetItem(para, 2)))
        );
        Py_INCREF(Py_None);
        return Py_None;

    }else if(strcmp(cmd, "GetFlag") == 0){
        fprintf(stderr, "Call GetFLag\n");
        int retvalue = GlobalVariable::GetFlag(
            PyString_AsString(PyTuple_GetItem(para, 1))
        );
        return Py_BuildValue("i", retvalue);

    }else if(strcmp(cmd, "DoMove") == 0){
        char active_event_name[20];
        strcpy(active_event_name, PyString_AsString(PyTuple_GetItem(para, 1)));
        PyObject* moving_list = PyTuple_GetItem(para, 2);
        std::queue<int> arg;
        for(int lx = 0;lx < (int)PyList_Size(moving_list);lx++){
            arg.push((int)PyInt_AsLong(PyList_GetItem(moving_list, lx)));
        }
        EnvGetEventPool()->operator[](active_event_name)->SetMovement(arg);
        Py_INCREF(Py_None);
        return Py_None;

    }else if(strcmp(cmd, "ShowSaveFile") == 0){
        EnvSetCertainScene("scene_save");
        // Wait for saving
        Py_INCREF(Py_None);
        return Py_None;

    }else if(strcmp(cmd, "WaitForMove") == 0){
        char active_event_name[20];
        strcpy(active_event_name, PyString_AsString(PyTuple_GetItem(para, 1)));
        Event* check_event = EnvGetEventPool()->operator[](active_event_name);
        while(check_event->Moving()); // TODO: use condition var
        Py_INCREF(Py_None);
        return Py_None;

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
        ScenePlay* scp = (ScenePlay*)(*((Scene**)(*env)["scene_play"]));
        if(scp == nullptr){
            fprintf(stderr, "nullptr HAHA\n");
        }
        scp->ChangeMap(EnvGetMap(map_name), start_x, start_y, dir);
        Py_INCREF(Py_None);
        return Py_None;

    }else{
        Py_INCREF(Py_None);
        return Py_None;
    }
}
