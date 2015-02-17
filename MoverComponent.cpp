#include "MoverComponent.h"

MoverComponent::MoverComponent(Object* _obj, 
                               std::vector<Vec2i> _auto_move_que) : obj(_obj){
    if(_auto_move_que.size() == 0){
        is_auto_move = false;
    }else{
        is_auto_move = true;
        auto_move_queue = _auto_move_que;
        auto_move_ptr = 0;
        Update();
    }
    return;
}

void MoverComponent::TickEvent(int delta_time){
    int dir_x[] = {0, -1, 1, 0};
    int dir_y[] = {1, 0, 0, -1};
    if(obj->status.sleep_ms){
        obj->status.sleep_ms = std::max(0, obj->status.sleep_ms - delta_time);
    }else if(obj->status.status == 1){
        obj->status.moving_step = std::min(obj->status.moving_step + delta_time, 16);
        if(obj->status.moving_step == 16){ // TODO: make this constant
            obj->status.x += dir_x[obj->status.moving_dir];
            obj->status.y += dir_y[obj->status.moving_dir];
            obj->status.status = 0;
            obj->status.moving_step = 0;
            Update();
        }
    }
    return;
}

void MoverComponent::Update(){
    if(move_queue.size()){
        Vec2i get_cmd = move_queue.front();
        obj->status.status = 1;
        obj->status.moving_step = 0;
        bool update_no_wait = false;
        switch(get_cmd.x){
        case CMD_TO:
            obj->status.moving_dir = get_cmd.y;
            obj->status.face_dir = get_cmd.y;
            break;
        case CMD_TOWARD:
            obj->status.moving_dir = obj->status.face_dir;
            break;
        case CMD_BACKWARD:
            obj->status.moving_dir = 3 - obj->status.face_dir;
            break;
        case CMD_FACETO:
            obj->status.face_dir = get_cmd.y;
            obj->status.moving_dir = get_cmd.y;
            obj->status.status = 0;
            update_no_wait = true;
            break;
        case CMD_SLEEP:
            obj->status.sleep_ms += get_cmd.y;
            obj->status.status = 0;
            update_no_wait = true;
            break;
        }
        move_queue.pop();
        if(update_no_wait)
            Update();
    }else if(is_auto_move){
        move_queue.push(auto_move_queue[auto_move_ptr++]);
        if(auto_move_ptr == auto_move_queue.size())
            auto_move_ptr = 0;
        Update();
    }
    return;
}

void MoverComponent::SetMoveQueue(const std::queue<Vec2i>& _move_queue){
    move_queue = _move_queue;
    Update();
    return;
}

bool MoverComponent::IsMoving(){
    if(move_queue.size())
        return true;

    return obj->status.status == 1;
}
