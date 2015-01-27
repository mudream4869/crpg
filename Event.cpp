#include <chrono>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <thread>

#include "Config.h"

#include "Event.h"
#include "SysCall.h"
#include "Env.h"
#include "Tool.h"
#include "PyLock.h"

#include "GlobalVariable.h"

Event::Event(const char* map_name, const char* str){
    char tmp[20];
    
    // TODO: garbage recycle
    // TODO: error handling

    // Set up PyObject
    
    sprintf(tmp, "scripts.%s", map_name);
    PySys_SetPath(".");
    
#ifdef DEBUG 
    fprintf(stderr, "Loading from %s....\n", tmp);
#endif

    this->p_module = PyImport_ImportModule(tmp);

#ifdef DEBUG
    if(this->p_module == NULL){
        fprintf(stderr, "Fail to import %s.\n", tmp);
        PyErr_Print();
        exit(1);
    }
#endif

    this->p_class = PyObject_GetAttrString(p_module, str);

#ifdef DEBUG
    if(this->p_class == NULL){
        fprintf(stderr, "Fail to get class '%s'.\n", str);
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
    this->p_inst = PyObject_CallObject(this->p_class, pArg);

#ifdef DEBUG
    if(this->p_inst == NULL){
        fprintf(stderr, "Fail to get new instance of %s\n", str);
        PyErr_Print();
        exit(1);
    }
#endif

    //TODO: kill pArg;
    this->p_func = PyObject_GetAttrString(this->p_inst, "Action");

#ifdef DEBUG
    if(this->p_func == NULL){
        fprintf(stderr, "Fail to get 'Action' function from %s\n", str);
        PyErr_Print();
        exit(1);
    }
#endif

    // Set up event config
    PyObject* p_config = PyObject_GetAttrString(this->p_inst, "config");

#ifdef DEBUG
    if(p_config == NULL){
        fprintf(stderr, "Fail to get 'config' dictionary from %s\n", str);
        PyErr_Print();
        exit(1);
    }
#endif

    char img_path[20];
    char trigger_condition_str[20];
    PyObject* p_img_path_str = PyDict_GetItemString(p_config, "image");
    //PyObject_Print(p_img_path_str, stderr, 0);
    PyObject* p_trig_cond_str = PyDict_GetItemString(p_config, "trigger_condition");
    //PyObject_Print(p_trig_cond_str, stderr, 0);
    
    if(p_img_path_str == NULL)
        img_path[0] = '\0';
    else
        strcpy(img_path, PyString_AsString(p_img_path_str));
    
    if(p_trig_cond_str == NULL)
        trigger_condition_str[0] = '\0';
    else
        strcpy(trigger_condition_str, PyString_AsString(p_trig_cond_str));

    this->is_solid = Py_True == PyDict_GetItemString(p_config, "solid");
    this->fixed_direction = Py_True == PyDict_GetItemString(p_config, "fixed_direction");
     
    // To load event name, event shouldn;t be empty

#ifdef DEBUG
    if(PyDict_GetItemString(p_config, "event_name") == NULL){
        fprintf(stderr, "Event name of %s should not be empty\n", str);
        exit(1);
    }
#endif

    strcpy(this->event_name, PyString_AsString(PyDict_GetItemString(p_config, "event_name")));
    
    if(PyDict_GetItemString(p_config, "priority") == NULL)
        this->priority = 0;
    else
        this->priority = (int)PyLong_AsLong(PyDict_GetItemString(p_config, "priority"));
    
    // display condititon 
    PyObject* p_cond_show = PyDict_GetItemString(p_config, "display_cond");
    if(p_cond_show != NULL){
        int cond_show_sz = PyList_Size(p_cond_show);
        for(int lx = 0;lx < cond_show_sz;lx++){
            PyObject* get_cond = PyList_GetItem(p_cond_show, lx);
            char* str_type = PyString_AsString(PyList_GetItem(get_cond, 0));
            char* var_name = PyString_AsString(PyList_GetItem(get_cond, 1));
            cond new_cond;
            strcpy(new_cond.var_name, var_name);
            if(strcmp("flag", str_type) == 0){
                new_cond.type = COND_TYPE_FLAG;
            }else if(strcmp("value", str_type) == 0){
                new_cond.type = COND_TYPE_VALUE;
                new_cond.limit_value = (int)PyLong_AsLong(PyList_GetItem(get_cond, 2));
            }
            display_cond.push_back(new_cond);
        }
    }

    PyObject* p_cond_reje = PyDict_GetItemString(p_config, "reject_cond");
    if(p_cond_reje != NULL){
        int cond_reje_sz = PyList_Size(p_cond_reje);
        for(int lx = 0;lx < cond_reje_sz;lx++){
            PyObject* get_cond = PyList_GetItem(p_cond_reje, lx);
            char* str_type = PyString_AsString(PyList_GetItem(get_cond, 0));
            char* var_name = PyString_AsString(PyList_GetItem(get_cond, 1));
            cond new_cond;
            strcpy(new_cond.var_name, var_name);
            if(strcmp("flag", str_type) == 0){
                new_cond.type = COND_TYPE_FLAG;
            }else if(strcmp("value", str_type) == 0){
                new_cond.type = COND_TYPE_VALUE;
                new_cond.limit_value = (int)PyLong_AsLong(PyList_GetItem(get_cond, 2));
            }
            reject_cond.push_back(new_cond);
        }
    }
    
    // TODO: clear this dirty thing
    EnvGetEventPool()->operator[](event_name) = this;

    if(img_path[0] != 0){
        this->tile_use = new Tile;
        char full_img_name[40];
        sprintf(full_img_name, "textures/%s", GetFileName(img_path));
        Image* tile_img = new Image(full_img_name);
        this->tile_use->SetImage(tile_img); 
        this->tile_use->SetSize(tile_img->GetWidth()/4, tile_img->GetHeight()/4);
    }else{
        this->tile_use = nullptr;
    }

    // Init the trigger condition
    if(strcmp(trigger_condition_str, "on chat") == 0)
        this->trigger_condition = TRIGGER_CONDITION_ON_CHAT;
    else  if(strcmp(trigger_condition_str, "on stand") == 0)
        this->trigger_condition = TRIGGER_CONDITION_ON_STAND;
    else if(strcmp(trigger_condition_str, "auto") == 0){

#ifdef DEBUG
        fprintf(stderr, "Event: trigger condition 'auto' is not provided.\n");
#endif

        this->trigger_condition = TRIGGER_CONDITION_AUTO;
    }else if(strcmp(trigger_condition_str, "sync") == 0)
        this->trigger_condition = TRIGGER_CONDITION_SYNC;
    else{

#ifdef DEBUG
        fprintf(stderr, "Event: trigger condition empty or not fit.\n");
        fprintf(stderr, "Warning : this event (%s) will sleep forever.\n", str);
#endif

        this->trigger_condition = TRIGGER_CONDITION_NULL;
    }
    
    //TODO: basic event setting
    //fprintf(stderr, "Basic setting....\n");
    for(int lx = 0;lx < 4;lx++){
        for(int ly = 0;ly < 4;ly++){
            walk_pos[lx][ly].x = ly;
            walk_pos[lx][ly].y = lx;
        }
    }

    event_status.status = 0;
    event_status.moving_dir = 0;
    event_status.moving_step = 0;
    // TODO: maybe read from config
    event_status.x = 7;
    event_status.y = 5;

#ifdef DEBUG    
    fprintf(stderr, "Event loads from %s ok\n", tmp);
#endif

    return;
}

Event::~Event(){
    if(tile_use != nullptr){
        delete tile_use->GetImage();
        delete tile_use;
    }
    Py_DECREF(this->p_inst);  
    Py_DECREF(this->p_module);  
    // TODO: kill p_?
    return;
}

bool Event::Condition(){
    for(int lx = 0;lx < display_cond.size();lx++){
        cond prc_cond = display_cond[lx];
        if(prc_cond.type == COND_TYPE_FLAG){
            if(GlobalVariable::GetFlag(prc_cond.var_name) == false)
                return false;
        }else if(prc_cond.type == COND_TYPE_VALUE){
            if(GlobalVariable::GetValue(prc_cond.var_name) < prc_cond.limit_value)
                return false;
        }
    }
    for(int lx = 0;lx < reject_cond.size(); lx++){
        cond prc_cond = reject_cond[lx];
        if(prc_cond.type == COND_TYPE_FLAG){
            if(GlobalVariable::GetFlag(prc_cond.var_name))
                return false;
        }else if(prc_cond.type == COND_TYPE_VALUE){
            if(GlobalVariable::GetValue(prc_cond.var_name) >= prc_cond.limit_value)
                return false;
        }
    }
    return true;
}

void Event::Action(HeroStatus hero_status, bool is_enter){
    // TODO: check the incref real implement
    // Important : unlock the `running` before return
    if(this->running.try_lock() == false) return;
    if(this->Condition() == false){
        this->running.unlock();
        return;
    }
    int dir_x[] = {0, -1, 1, 0};
    int dir_y[] = {1, 0, 0, -1};
    bool fit_cond = false;
    if(this->trigger_condition == TRIGGER_CONDITION_ON_CHAT){
        if(this->is_solid == false)
            fit_cond = is_enter and 
                    hero_status.moving_step == 0 and
                    event_status.x == hero_status.x and
                    event_status.y == hero_status.y;
        else
            fit_cond = is_enter and 
                    hero_status.moving_step == 0 and
                    event_status.x == hero_status.x + dir_x[hero_status.moving_dir] and
                    event_status.y == hero_status.y + dir_y[hero_status.moving_dir];

        if(fit_cond and this->fixed_direction == false){
            event_status.moving_dir = 3 - hero_status.moving_dir; 
        }
    }else if(this->trigger_condition == TRIGGER_CONDITION_ON_STAND){
        fit_cond = hero_status.moving_step == 0 and
                   event_status.x == hero_status.x and
                   event_status.y == hero_status.y;
    }else if(this->trigger_condition == TRIGGER_CONDITION_AUTO){
        // TODO: event_auto
    }else if(this->trigger_condition == TRIGGER_CONDITION_SYNC){
        fit_cond = true;
    }

    if(fit_cond == false){
        this->running.unlock();
        return;
    }

    std::thread torun(
        [this]{
            PyLock();
            auto state = Py_NewInterpreter(); 
            PyEval_RestoreThread(state);

#ifdef DEBUG
            PyErr_Clear();
#endif

            PyObject* pArg = Py_BuildValue("()");
            PyObject* ret = PyObject_CallObject(this->p_func, pArg);

#ifdef DEBUG
            if(PyErr_Occurred() != NULL){
                fprintf(stderr, "Error occur at calling event %s\n", event_name);
                PyErr_Print();
                exit(1);
            }
#endif

            Py_XDECREF(pArg);
            Py_XDECREF(ret);
            //PyEval_SaveThread();
            //Py_EndInterpreter(state);
            PyUnlock();
            this->running.unlock();
        }
    );
    torun.detach();
    return;
}

bool Event::IsSolid()const{
    return this->is_solid;
}

Vec2i Event::Position()const{
    return {event_status.x, event_status.y};
}

int Event::GetPriority(){
    return this->priority;
}

void Event::SetMovement(std::queue<int> _move_queue){
    this->move_queue = _move_queue;
    CheckMovement();
    return;
}

void Event::CheckMovement(){
    if(this->move_queue.size()){
        event_status.status = 1;
        event_status.moving_step = 0;
        event_status.moving_dir = this->move_queue.front();
        move_queue.pop();
    }
    return;
}

bool Event::Moving()const{
    if(move_queue.size())
        return true;
    return event_status.status == 1;
}

void Event::TickEvent(int delta_time){
    int dir_x[] = {0, -1, 1, 0};
    int dir_y[] = {1, 0, 0, -1};
    if(event_status.status == 1){
        event_status.moving_step = std::min(event_status.moving_step + delta_time, 16);
        if(event_status.moving_step == 16){ // TODO: make this constant
            event_status.x += dir_x[event_status.moving_dir];
            event_status.y += dir_y[event_status.moving_dir];
            event_status.status = 0;
            event_status.moving_step = 0;
            CheckMovement();
        }
    }
    return;
}

void Event::Render(float left, float top){
    // TODO: make 2 environment
    //if(this->Condition() == false) return;
    int dir_x[] = {0, -1, 1, 0};
    int dir_y[] = {1, 0, 0, -1};
    if(this->Condition() == false) return;
    
    if(tile_use != nullptr){
        float paint_x = ((float)event_status.x + event_status.moving_step*dir_x[event_status.moving_dir]/16.0)/10.0*2 + left;
        float paint_y = ((float)event_status.y + event_status.moving_step*dir_y[event_status.moving_dir]/16.0)/10.0*2 + top;
        Vec2i sz = tile_use->GetSize();
        paint_y = paint_y + 1/(float)5 - sz.y/(float)32*0.2;
        this->tile_use->Render(
            paint_x, paint_y,
            sz.x/(float)32*0.2,
            sz.y/(float)32*0.2, 
            this->walk_pos[event_status.moving_dir][(event_status.moving_step/2)%4].x,
            this->walk_pos[event_status.moving_dir][(event_status.moving_step/2)%4].y,
        2);
    }
    return;
}

HeroStatus Event::GetStatus(){
    return event_status;
}

void Event::SetStatus(HeroStatus status){
    event_status = status;
    return;
} 
void Event::SetPosition(int x, int y){
    event_status.x = x;
    event_status.y = y;
    return;
}
