#ifndef EVENT_DEF
#define EVENT_DEF

#include <Python/Python.h>
#include <atomic>
#include <queue>
#include "Tile.h"
#include "Type.h"

const int TRIGGER_CONDITION_NULL = 0;
const int TRIGGER_CONDITION_ON_CHAT = 1;
const int TRIGGER_CONDITION_ON_STAND= 2;
const int TRIGGER_CONDITION_AUTO = 3;
const int TRIGGER_CONDITION_SYNC = 4;

class Event{
public:
    Event(const char* map_name, const char* str);
    ~Event();
    
    void Action(HeroStatus hero_status, bool is_enter);
    void TickEvent(int delta_time);
    void Render(float left, float top);
    bool IsSolid()const;
    Vec2i Position()const;
    void SetMovement(std::queue<int> _move_queue);
    bool Moving()const;
    int trigger_condition;
    // TODO: check if it is ok
    std::atomic<bool> running;
    
    HeroStatus GetStatus();
    void SetStatus(HeroStatus status); 
    void SetPosition(int x, int y);

private:
    void CheckMovement();
    bool is_solid;
    bool fixed_direction;
    HeroStatus event_status;
    Vec2i walk_pos[4][4]; 
    char event_name[20];
    
    std::queue<int> move_queue;

    PyObject* p_class;
    PyObject* p_func; 
    PyObject* p_inst;
    PyObject* p_obj;
    Tile* tile_use;
};

#endif
