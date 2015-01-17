#include <chrono>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <thread>
#include "Event.h"
#include "SysCall.h"
#include "Env.h"
#include "Tool.h"

Event::Event(const char* map_name, const char* str){
    char tmp[20];
    
    // TODO: garbage recycle
    // TODO: error handling

    // Set up PyObject
    sprintf(tmp, "scripts.%s", map_name);
    printf("Event: ready to load %s\n", tmp);
    PyObject* p_module = PyImport_ImportModule(tmp);
    this->p_class = PyObject_GetAttrString(p_module, str);
    //PyObject* p_get_class_func = PyObject_GetAttrString(p_module, "EventTalk");
    PyObject_Print(this->p_class, stderr, 0);

    PyMethodDef *callback = new PyMethodDef;

    callback->ml_name = "func";
    callback->ml_meth = Sys::SysCall;
    callback->ml_flags = 1;

    PyObject* pcb = PyCFunction_New(callback, NULL);
    PyObject* pArg = Py_BuildValue("(O)", pcb);

    this->p_inst = PyObject_CallObject(this->p_class, pArg);
    //TODO: kill pArg;
    this->p_func = PyObject_GetAttrString(this->p_inst, "Action");
    PyObject_Print(this->p_func, stderr, 0);

    // Set up event config
    PyObject* p_config = PyObject_GetAttrString(this->p_inst, "config");

    char img_path[20];
    char trigger_condition_str[20];
    PyObject* p_img_path_str = PyDict_GetItemString(p_config, "image");
    PyObject_Print(p_img_path_str, stderr, 0);
    PyObject* p_trig_cond_str = PyDict_GetItemString(p_config, "trigger_condition");
    PyObject_Print(p_trig_cond_str, stderr, 0);

    strcpy(img_path, PyString_AsString(p_img_path_str));
    strcpy(trigger_condition_str, PyString_AsString(p_trig_cond_str));

    //fprintf(stderr, "Ready to load solid setting\n");
    this->is_solid = strcmp(
        "true",
        PyString_AsString(PyDict_GetItemString(p_config, "solid"))
    ) == 0;
    this->fixed_direction = strcmp(
        "true", 
        PyString_AsString(PyDict_GetItemString(p_config, "fixed_direction"))
    ) == 0;
     
    strcpy(this->event_name, PyString_AsString(PyDict_GetItemString(p_config, "event_name")));
    
    EnvGetEventPool()->operator[](event_name) = this;

    //fprintf(stderr, "set up solid\n");
    this->tile_use = new Tile;
    char full_img_name[40];
    sprintf(full_img_name, "textures/%s", GetFileName(img_path));
    Image* tile_img = new Image(full_img_name);
    this->tile_use->SetImage(tile_img); 
    this->tile_use->SetSize(tile_img->GetWidth()/4, tile_img->GetHeight()/4);

    // Init the trigger condition
    if(strcmp(trigger_condition_str, "on chat") == 0)
        this->trigger_condition = TRIGGER_CONDITION_ON_CHAT;
    else  if(strcmp(trigger_condition_str, "on stand") == 0)
        this->trigger_condition = TRIGGER_CONDITION_ON_STAND;
    else if(strcmp(trigger_condition_str, "auto") == 0)
        this->trigger_condition = TRIGGER_CONDITION_AUTO;
    else if(strcmp(trigger_condition_str, "sync") == 0)
        this->trigger_condition = TRIGGER_CONDITION_SYNC;
    else
        this->trigger_condition = TRIGGER_CONDITION_NULL;

    this->running = false;
    
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
    
    fprintf(stderr, "Event: Event load %s ok\n", tmp);
    return;
}

Event::~Event(){
    delete tile_use->GetImage();
    delete tile_use;
    // TODO: kill p_?
    return;
}

void Event::Action(HeroStatus hero_status, bool is_enter){
    // TODO: check the incref real implement
    // TODO: torun recycle 
    static int dir_x[] = {0, -1, 1, 0};
    static int dir_y[] = {1, 0, 0, -1};
    
    if(this->running) return;
    bool fit_cond = false;
    if(this->trigger_condition == TRIGGER_CONDITION_ON_CHAT){
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
        fit_cond = true;
    }else if(this->trigger_condition == TRIGGER_CONDITION_SYNC){
        // TODO: event_sync
    }
    if(fit_cond == false) return;

    this->running = true;
    std::thread* torun = new std::thread(
        [this]{
            PyObject* pArg = Py_BuildValue("()");
            PyObject* ret = PyObject_CallObject(this->p_func, pArg);
            this->running = false;
        }
    );
    fprintf(stderr, "Event Action\n");
    return;
}


bool Event::IsSolid()const{
    return this->is_solid;
}

Vec2i Event::Position()const{
    return {event_status.x, event_status.y};
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
    static int dir_x[] = {0, -1, 1, 0};
    static int dir_y[] = {1, 0, 0, -1};
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
    static int dir_x[] = {0, -1, 1, 0};
    static int dir_y[] = {1, 0, 0, -1};
    this->tile_use->Render(
        ((float)event_status.x + event_status.moving_step*dir_x[event_status.moving_dir]/16.0)/10.0*2 + left,
        ((float)event_status.y + event_status.moving_step*dir_y[event_status.moving_dir]/16.0)/10.0*2 + top - 0.2,
        0.2, 0.3, 
        this->walk_pos[event_status.moving_dir][(event_status.moving_step/2)%4].x,
        this->walk_pos[event_status.moving_dir][(event_status.moving_step/2)%4].y,
    2);
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
