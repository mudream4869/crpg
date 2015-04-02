#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "WindowMsgSelect.h"

#include "Constant.h"

WindowMsgSelect::WindowMsgSelect(char* _options[], int count)
    : WindowBlockType(0.7, 0.8, 0.6, 0.4){
    for(int lx = 0;lx < count;lx++){
        char* new_str = new char[strlen(_options[lx]) + 2];
        strcpy(new_str, _options[lx]);
        options.push_back(new_str);
    }
    ptr = 0;
    Update();
    return;
}

WindowMsgSelect::~WindowMsgSelect(){
    for(int lx = 0;lx < options.size();lx++)
        delete options[lx];
    return;
}

void WindowMsgSelect::InputEvent(Input inp){
    if(inp.type == INPUT_NORMAL_KEY_DOWN and inp.normal_key == 13){
        WindowBlockType::ret_value = NewWriteType(WRITE_INT, ptr, "");
        delete this;
        return;
    }
    int dir = Input2Dir(inp);
    bool update = false;
    if(dir == DIR_UP and ptr)
        ptr--, update = true;
    else if(dir == DIR_DOWN and ptr + 1 < options.size())
        ptr++, update = true;
    if(update)
        this->Update();
    return;
}

void WindowMsgSelect::Update(){
    Clear();
    for(int lx = 0;lx < options.size();lx++){
        DrawText(0.1, 0.16*lx + 0.135, options[lx]);
        if(lx == ptr)
            DrawBox(0.08, 0.16*lx + 0.03, 0.4, 0.14, {0.7, 0.3, 0.4, 0.5});
    }
    return;
}