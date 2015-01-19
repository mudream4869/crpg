#ifndef EVENT_DEF
#define EVENT_DEF

#include <Python/Python.h>
#include <mutex>
#include <queue>
#include "Tile.h"
#include "Type.h"

const int TRIGGER_CONDITION_NULL = 0;
const int TRIGGER_CONDITION_ON_CHAT = 1;
const int TRIGGER_CONDITION_ON_STAND= 2;
const int TRIGGER_CONDITION_AUTO = 3;
const int TRIGGER_CONDITION_SYNC = 4;

const int COND_TYPE_FLAG = 0;
const int COND_TYPE_VALUE = 1;
const int COND_TYPE_PRIVATE_FLAG = 2; // TODO

class Event{
public:
    Event(const char* map_name, const char* str);
    ~Event();
    
    void Action(HeroStatus hero_status, bool is_enter);
    bool Condition();
    
    void TickEvent(int delta_time);
    
    void Render(float left, float top);
    int GetPriority();

    bool IsSolid()const;
    
    Vec2i Position()const;
    void SetMovement(std::queue<int> _move_queue);
    bool Moving()const;
    
    int trigger_condition;
    
    std::mutex running;
    
    HeroStatus GetStatus();
    void SetStatus(HeroStatus status); 
    void SetPosition(int x, int y);
    PyObject* p_func;

private:
    void CheckMovement();
    bool is_solid;
    bool fixed_direction;
    HeroStatus event_status;
    Vec2i walk_pos[4][4]; 
    char event_name[20];
   
    int priority;
     
    std::queue<int> move_queue;
    
    struct cond{
        int type;
        char var_name[20];
        int limit_value;
    };
    std::vector<cond> display_cond;
    
    PyThreadState* save_state;

    PyObject* p_class;
    PyObject* p_inst;
    PyObject* p_obj;
    Tile* tile_use;
};

#endif
