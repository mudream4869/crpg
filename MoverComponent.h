#ifndef MOVERCOMPONENT_DEF
#define MOVERCOMPONENT_DEF

#include <queue>

#include "Event.h"
#include "Type.h"

class Event;

class MoverComponent{
public:
    MoverComponent(Event* _obj);
    void TickEvent(int delta_time);
    void Update();

    void SetMoveQueue(const std::queue<int>& _move_queue);
    bool IsMoving();

private:
    std::queue<int> move_queue;
    Event* obj;
};

#endif
