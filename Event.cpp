#include <chrono>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <thread>

#include "Config.h"

#include "Event.h"
#include "SysCall.h"
#include "Tool.h"

#include "GlobalVariable.h"

#include "SceneSave.h"
#include "ScenePlay.h"

std::map<const char*, Event*, StrComp> Event::event_pool;  

std::vector<Event::cond> Event::CondList2Vector(PyObject* cond_list){
    std::vector<cond> ret;
    if(cond_list != NULL){
        int cond_sz = PyList_Size(cond_list);
        for(int lx = 0;lx < cond_sz;lx++){
            PyObject* get_cond = PyList_GetItem(cond_list, lx);
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
            ret.push_back(new_cond);
        }
    }
    return ret;
}

void Event::PyObject2String(PyObject* p_str, char* str_ptr, const char* default_str){
   if(p_str == NULL)
       strcpy(str_ptr, default_str);
    else
        strcpy(str_ptr, PyString_AsString(p_str));
    return;
}

Event::Event(const char* map_name, const char* str){
    char tmp[20];
    script = new Script(map_name, str);     

    PyObject* p_config = script->GetAttr("config");

#ifdef DEBUG
    if(p_config == NULL){
        fprintf(stderr, "Fail to get 'config' dictionary from %s\n", str);
        PyErr_Print();
        exit(1);
    }
#endif

    char img_path[20];
    char trigger_condition_str[20];
    Event::PyObject2String(PyDict_GetItemString(p_config, "image"), img_path);
    Event::PyObject2String(PyDict_GetItemString(p_config, "trigger_condition"), trigger_condition_str);

    this->is_solid = Py_True == PyDict_GetItemString(p_config, "solid");
    this->fixed_direction = Py_True == PyDict_GetItemString(p_config, "fixed_direction");
    this->is_stay = Py_True == PyDict_GetItemString(p_config, "stay");
     
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
    display_cond = Event::CondList2Vector(p_cond_show);

    PyObject* p_cond_reje = PyDict_GetItemString(p_config, "reject_cond");
    reject_cond = Event::CondList2Vector(p_cond_reje);
    
    Event::event_pool[event_name] = this;

    if(img_path[0] != 0){
        char full_img_name[40];
        sprintf(full_img_name, "textures/%s", GetFileName(img_path));
        Image* tile_img = new Image(full_img_name);
        this->tile_use = new Tile(tile_img->GetWidth()/4, tile_img->GetHeight()/4, tile_img);
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
    
    std::vector<Vec2i> auto_move_que;
    PyObject* p_auto_move_que = PyDict_GetItemString(p_config, "auto_move");
    int q_sz = PyList_Size(p_auto_move_que);
    for(int lx = 0;lx < q_sz;lx++){
        PyObject* get_cmd = PyList_GetItem(p_auto_move_que, lx);
        int cmd_type = (int)PyInt_AsLong(PyList_GetItem(get_cmd, 0));
        int l_arg = (int)PyInt_AsLong(PyList_GetItem(get_cmd, 1));
        auto_move_que.push_back(Vec2i(cmd_type, l_arg));
    }
    
    bool is_chase = Py_True == PyDict_GetItemString(p_config, "chase_move");
    
    mover_component = new MoverComponent(this);
    
    if(auto_move_que.size()){
        mover_component->SetAutoQueue(auto_move_que);
    }else if(is_chase){
        mover_component->SetChase();
    }
    
    graphic_component = new GraphicComponent(this);

#ifdef DEBUG    
    fprintf(stderr, "Event loads from %s ok\n", tmp);
#endif

    return;
}

Event::~Event(){
    Event::event_pool.erase(event_name);
    delete script;
    delete mover_component;
    delete graphic_component;
    
    if(tile_use != nullptr){
        delete tile_use->GetImage();
        delete tile_use;
    }
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

void Event::Action(bool is_enter){
    // TODO: check the incref real implement
    if(this->Condition() == false){
        return;
    }
    int dir_x[] = {0, -1, 1, 0};
    int dir_y[] = {1, 0, 0, -1};
    bool fit_cond = false;
    HeroStatus hero_status = ScenePlay::scene_play->hero_use->status;
    if(this->trigger_condition == TRIGGER_CONDITION_ON_CHAT){
        if(this->is_solid == false)
            fit_cond = is_enter and 
                    hero_status.moving_step == 0 and
                    status.x == hero_status.x and
                    status.y == hero_status.y;
        else
            fit_cond = is_enter and 
                    hero_status.moving_step == 0 and
                    status.x == hero_status.x + dir_x[hero_status.moving_dir] and
                    status.y == hero_status.y + dir_y[hero_status.moving_dir];
        /* weird */
        if(fit_cond and this->fixed_direction == false){
            status.face_dir = 3 - hero_status.moving_dir; 
        }
    }else if(this->trigger_condition == TRIGGER_CONDITION_ON_STAND){
        fit_cond = hero_status.moving_step == 0 and
                   status.x == hero_status.x and
                   status.y == hero_status.y;
    }else if(this->trigger_condition == TRIGGER_CONDITION_AUTO){
        // TODO: event_auto
    }else if(this->trigger_condition == TRIGGER_CONDITION_SYNC){
        fit_cond = true;
    }

    if(fit_cond == false){
        return;
    }
    
    SceneSave::scene_save->Snap();
    script->Shell();
    return;
}

bool Event::IsSolid()const{
    return this->is_solid;
}

int Event::GetPriority(){
    return this->priority;
}

void Event::TickEvent(int delta_time){
    mover_component->TickEvent(delta_time);
    
    return;
}

void Event::Render(float left, float top){
    if(this->Condition() == false) return;
    graphic_component->Render(left, top); 
    return;
}
