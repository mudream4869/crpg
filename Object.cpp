#include "Object.h"

Object::Object(){
    is_stay = false;
    speed = 0;
    status.moving_step = 0;
    return; 
}

Vec2i Object::GetPosition(){
    return {status.x, status.y};
}

Vec2i Object::GetNextPosition(){
    int dir_x[] = {0, -1, 1, 0};
    int dir_y[] = {1, 0, 0, -1};
    if(status.moving_step)
        return { status.x + dir_x[status.moving_dir],
             status.y + dir_y[status.moving_dir]};
    else
        return GetPosition();
}

void Object::SetPosition(int x, int y){
    status.x = x, status.y = y;
    return;
}
