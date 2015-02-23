#include "Object.h"

Object::Object(){
    is_stay = false;
    speed = 0;
}

Vec2i Object::GetPosition(){
    return {status.x, status.y};
}

void Object::SetPosition(int x, int y){
    status.x = x, status.y = y;
    return;
}
