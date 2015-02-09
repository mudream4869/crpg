#include "Object.h"

Object::Object(){}

Vec2i Object::GetPosition(){
    return {status.x, status.y};
}

void Object::SetPosition(int x, int y){
    status.x = x, status.y = y;
    return;
}
