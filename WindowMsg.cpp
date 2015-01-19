#include <cstdlib>
#include "WindowMsg.h"

WindowMsg::WindowMsg(float _left, float _top, float _width, float _height, const char* str)
    :Window(_left, _top, _width, _height){
    printf("Init the msg: [%s]\n", str);
    ptr = 0;
    msg = new char[strlen(str) + 1];
    strcpy(msg, str);
    return;
}

WindowMsg::~WindowMsg(){
    cv.notify_all();
    fprintf(stderr, "notify all!\n");
    delete[] msg;
    return;
}

void WindowMsg::TickEvent(int a){
    // TODO: clear dirty thing
    if(msg[ptr] == 0){
        return;
    }
    char tmp = msg[ptr+1];
    msg[ptr+1] = 0;
    this->DrawText(0.1, 0.1, msg) ;
    msg[ptr+1] = tmp;
    ptr++;
    return;
}

bool WindowMsg::IsOk()const{
    return msg[ptr] == 0;
}
// Blocking syscall
std::condition_variable* WindowMsg::GetSignal(){
    return &(this->cv);
}
