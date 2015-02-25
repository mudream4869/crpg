#ifndef MOVERCOMPONENT_DEF
#define MOVERCOMPONENT_DEF

#include <queue>
#include <vector>
#include "Object.h"
#include "Type.h"

class Object;

const int CMD_TO = 0;
const int CMD_TOWARD = 1;
const int CMD_BACKWARD = 2;
const int CMD_FACETO = 3;
const int CMD_SLEEP = 4;
const int CMD_SPEED = 5;

const int CONTROL_TYPE_NULL = 0;
const int CONTROL_TYPE_AUTO = 1;
const int CONTROL_TYPE_CHASE = 2;

class MoverComponent{
public:
    MoverComponent(Object* _obj);
    void TickEvent(int delta_time);
    void Update();
    
    void SetAutoQueue(std::vector<Vec2i> _auto_que = std::vector<Vec2i>());
    void SetQueue(std::queue<Vec2i> _move_queue = std::queue<Vec2i>());
    void SetChase();

    bool IsMoving();

private:
    
    bool ExeCmd(Vec2i cmd);
    
    int control_type;

    std::queue<Vec2i> move_queue;
    std::vector<Vec2i> auto_move_queue;
    int auto_move_ptr;
    
    Object* obj;
};

#endif
