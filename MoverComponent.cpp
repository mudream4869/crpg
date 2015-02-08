#include "MoverComponent.h"


MoverComponent::MoverComponent(Event* _obj) : obj(_obj){
}

void MoverComponent::TickEvent(int delta_time){
    int dir_x[] = {0, -1, 1, 0};
    int dir_y[] = {1, 0, 0, -1};
    if(obj->event_status.status == 1){
        obj->event_status.moving_step = std::min(obj->event_status.moving_step + delta_time, 16);
        if(obj->event_status.moving_step == 16){ // TODO: make this constant
            obj->event_status.x += dir_x[obj->event_status.moving_dir];
            obj->event_status.y += dir_y[obj->event_status.moving_dir];
            obj->event_status.status = 0;
            obj->event_status.moving_step = 0;
            Update();
        }
    }
    return;
}

void MoverComponent::Update(){
    if(move_queue.size()){
        obj->event_status.status = 1;
        obj->event_status.moving_step = 0;
        obj->event_status.moving_dir = move_queue.front();
        move_queue.pop();
    }
    return;
}

void MoverComponent::SetMoveQueue(const std::queue<int>& _move_queue){
    move_queue = _move_queue;
    Update();
    return;
}

bool MoverComponent::IsMoving(){
    if(move_queue.size())
        return true;

    return obj->event_status.status == 1;
}   
