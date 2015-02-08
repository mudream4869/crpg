#ifndef MOVERCOMPONENT_DEF
#define MOVERCOMPONENT_DEF

#include <queue>

#include "Object.h"
#include "Type.h"

class Object;

class MoverComponent{
public:
    MoverComponent(Object* _obj);
    void TickEvent(int delta_time);
    void Update();

    void SetMoveQueue(const std::queue<int>& _move_queue);
    bool IsMoving();

private:
    std::queue<int> move_queue;
    Object* obj;
};

#endif
