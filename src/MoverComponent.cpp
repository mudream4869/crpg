#include <cstdio>
#include <cstdlib>
#include "MoverComponent.h"
#include "ScenePlay.h"

MoverComponent::MoverComponent(Object* _obj) : obj(_obj){
    control_type = CONTROL_TYPE_NULL;
    return;
}

bool MoverComponent::IsQueued() const {
    return control_type == CONTROL_TYPE_NULL and move_queue.size();
}

void MoverComponent::SetAutoQueue(std::vector<Vec2i> _auto_move_que){
    control_type = CONTROL_TYPE_AUTO;
    auto_move_queue = _auto_move_que;
    auto_move_ptr = 0;
    return;
}

void MoverComponent::SetQueue(std::queue<Vec2i> _move_queue){
    control_type = CONTROL_TYPE_NULL;
    move_queue = _move_queue;
    return;
}

void MoverComponent::SetChase(){
    control_type = CONTROL_TYPE_CHASE;
    return;
}

bool MoverComponent::ExeCmd(Vec2i get_cmd){
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
    case CMD_SPEED:
        obj->speed = get_cmd.y;
        obj->status.status = 0;
        update_no_wait = true;
        break; 
    }
    return update_no_wait;
}

void MoverComponent::TickEvent(int delta_time){
    int dir_x[] = {0, -1, 1, 0};
    int dir_y[] = {1, 0, 0, -1};
    if(obj->status.sleep_ms){
        obj->status.sleep_ms = std::max(0, obj->status.sleep_ms - delta_time);
        return;
    }

    if(obj->status.status == 1){
        if(ScenePlay::scene_play->CanDo(obj->status.x, obj->status.y, obj->status.moving_dir, obj) == false)
            return;
        obj->status.moving_step = std::min(obj->status.moving_step + delta_time*(1<<obj->speed), 16);
        if(obj->status.moving_step == 16){ // TODO: make this constant
            if(obj->is_stay == false){
                obj->status.x += dir_x[obj->status.moving_dir];
                obj->status.y += dir_y[obj->status.moving_dir];
            }
            obj->status.status = 0;
            obj->status.moving_step = 0;
        }
        return;
    }

    switch(control_type){
    case CONTROL_TYPE_NULL:{
        bool cont = true;
        while(move_queue.size() and cont){
            cont = ExeCmd(move_queue.front());
            move_queue.pop();
        }
        break;
    }case CONTROL_TYPE_AUTO:{
        if(auto_move_queue.size()){
            ExeCmd(auto_move_queue[auto_move_ptr]);
            auto_move_ptr = (auto_move_ptr+1)%auto_move_queue.size();
        }
        break;
    }case CONTROL_TYPE_CHASE:{
        int hx = ScenePlay::scene_play->hero_use->status.x;
        int hy = ScenePlay::scene_play->hero_use->status.y;
        if(rand()&1){
            // x axis
            if(obj->status.x > hx){
                if(ScenePlay::scene_play->CanDo(obj->status.x, obj->status.y, 1, obj))
                    ExeCmd(Vec2i(CMD_TO, 1));
            }else if(obj->status.x < hx){
                if(ScenePlay::scene_play->CanDo(obj->status.x, obj->status.y, 2, obj))
                    ExeCmd(Vec2i(CMD_TO, 2));
            }
        }else{
            // y asix
            if(obj->status.y > hy){
                if(ScenePlay::scene_play->CanDo(obj->status.x, obj->status.y, 3, obj))
                    ExeCmd(Vec2i(CMD_TO, 3));
            }else if(obj->status.y < hy){
                if(ScenePlay::scene_play->CanDo(obj->status.x, obj->status.y, 0, obj))
                    ExeCmd(Vec2i(CMD_TO, 0));
            }
        }

        break;
    }}
    return;
}

void MoverComponent::Update(){
    return;
}

bool MoverComponent::IsMoving(){
    if(move_queue.size())
        return true;

    return obj->status.status == 1;
}
