#include <cstdlib>
#include "WindowMsg.h"

WindowMsg::WindowMsg(float _left, float _top, float _width, float _height, const char* str)
    :Window(_left, _top, _width, _height){
    printf("Init the msg: [%s]\n", str);
    isok = false; 
    ptr = -1;
    msg = new char[strlen(str) + 1];
    strcpy(msg, str);
    ptr_x = 0.1, ptr_y = 0.1;
    return;
}

void WindowMsg::TickEvent(int a){
    // TODO: clear dirty thing
    if(isok) return;
    ptr++;
    if(msg[ptr] == 0){
        isok = true;
        return;
    }
    char c[2] = {msg[ptr], 0};
    ptr_x += 0.06;
    if(ptr_x > width)
        ptr_x = 0.1, ptr_y = ptr_y + 0.1;
    this->DrawText(ptr_x, ptr_y, c) ;
    return;
}

bool WindowMsg::IsOk()const{
    return isok;
}
