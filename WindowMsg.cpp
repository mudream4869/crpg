#include <cstdlib>
#include "WindowMsg.h"

WindowMsg::WindowMsg(const char* str)
    :WindowBlockType(0.1, 1.5, 1.8, 0.4){
    printf("Init the msg: [%s]\n", str);
    ptr = 0;
    msg = new char[strlen(str) + 1];
    strcpy(msg, str);
    return;
}

WindowMsg::~WindowMsg(){
    //cv.notify_all();
    //fprintf(stderr, "notify all!\n");
    delete[] msg;
    return;
}

void WindowMsg::InputEvent(Input inp){
    if(inp.InputType != INPUT_KEYPRESS) return;
    if(inp.Key != 13) return;
    if(msg[ptr] == 0)
        delete this;
    return;
}

void WindowMsg::TickEvent(int a){
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

// Blocking syscall
/*std::condition_variable* WindowMsg::GetSignal(){
    return &(this->cv);
}*/
