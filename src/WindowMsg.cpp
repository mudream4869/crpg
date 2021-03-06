#include <cstdlib>
#include <cstring>
#include "WindowMsg.h"

WindowMsg::WindowMsg(const wchar_t* str)
    :WindowBlockType(0.1, 1.5, 1.8, 0.4){
    //printf("Init the msg: [%s]\n", str);
    ptr = 0;
    msg = new wchar_t[wcslen(str) + 1];
    wcscpy(msg, str);
    return;
}

WindowMsg::~WindowMsg(){
    //cv.notify_all();
    //fprintf(stderr, "notify all!\n");
    delete[] msg;
    return;
}

void WindowMsg::InputEvent(Input inp){
    if(inp.type != INPUT_NORMAL_KEY_DOWN) return;
    if(inp.normal_key != 13) return;
    if(msg[ptr] != 0){
        for(int lx = 0;lx < 10;lx++)
            TickEvent(1);
    }else
        delete this;
    return;
}

void WindowMsg::TickEvent(int a){
    if(msg[ptr] == 0){
        return;
    }
    wchar_t tmp = msg[ptr+1];
    msg[ptr+1] = 0;
    this->DrawWText(0.1, 0.1, msg) ;
    msg[ptr+1] = tmp;
    ptr++;
    return;
}

// Blocking syscall
/*std::condition_variable* WindowMsg::GetSignal(){
    return &(this->cv);
}*/
