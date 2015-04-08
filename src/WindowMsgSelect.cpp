#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "WindowMsgSelect.h"

#include "Constant.h"

WindowMsgSelect::WindowMsgSelect(std::vector<std::wstring> _options)
    : WindowBlockType(0.7, 0.8, 0.6, 0.4){
    options = _options;
    ptr = 0;
    Update();
    return;
}

WindowMsgSelect::~WindowMsgSelect(){
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
    if(dir == Constant::DIR_UP and ptr)
        ptr--, update = true;
    else if(dir == Constant::DIR_DOWN and ptr + 1 < options.size())
        ptr++, update = true;
    if(update)
        this->Update();
    return;
}

void WindowMsgSelect::Update(){
    Clear();
    for(int lx = 0;lx < options.size();lx++){
        DrawWText(0.1, 0.16*lx + 0.135, (wchar_t*)options[lx].c_str());
        if(lx == ptr)
            DrawBox(0.08, 0.16*lx + 0.03, 0.4, 0.14, {0.7, 0.3, 0.4, 0.5});
    }
    return;
}
