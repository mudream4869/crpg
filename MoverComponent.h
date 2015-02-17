#ifndef MOVERCOMPONENT_DEF
#define MOVERCOMPONENT_DEF

#include <queue>

#include "Object.h"
#include "Type.h"

class Object;

const int CMD_TO = 0;
const int CMD_TOWARD = 1;
const int CMD_BACKWARD = 2;
const int CMD_FACETO = 3;
const int CMD_SLEEP = 4;

class MoverComponent{
public:
    MoverComponent(Object* _obj);
    void TickEvent(int delta_time);
    void Update();

    void SetMoveQueue(const std::queue<Vec2i>& _move_queue);
    bool IsMoving();

private:
    std::queue<Vec2i> move_queue;
    Object* obj;
};

#endif
