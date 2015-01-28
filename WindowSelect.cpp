#include "WindowSelect.h"

#include "Constant.h"

WindowSelect::WindowSelect(float _left, float _top, float _width, float _height,
            std::function<void(int)>cb,
            std::function<void(int)>ch,
            char** _items, int itemcount):Window(_left, _top, _width, _height){
    choose_callback = cb;
    change_callback = ch;
    for(int lx = 0;lx < itemcount;lx++){
        char* new_str = new char[strlen(_items[lx]) + 2];
        strcpy(new_str, _items[lx]);
        items.push_back(new_str);
    }
    select_index = 0;
    this->Update();
    return;
}

WindowSelect::~WindowSelect(){
    for(int lx = 0;lx < items.size();lx++){
        delete[] items[lx];
    }
    return;
}

void WindowSelect::InputEvent(Input inp){
    bool up = false, down = false;
    if(inp.type == INPUT_NORMAL_KEY_DOWN){
        if(inp.normal_key == 27){
            choose_callback(-1);
            return;
        }else if(inp.normal_key == 13){
            choose_callback(select_index);
            return;
        }
    }
    int dir = Input2Dir(inp);
            
    if(dir == DIR_UP and select_index > 0){
        select_index--;
        this->Update();
    }
    if(dir == DIR_DOWN and select_index+1 < items.size()){
        select_index++;
        this->Update();
    }
    return;
}

void WindowSelect::Update(){
    Clear();
    change_callback(select_index);
    for(int lx = 0;lx < items.size();lx++){
        DrawText(0.1, 0.16*lx + 0.135, items[lx]);
        if(lx == select_index)
            DrawBox(0.08, 0.16*lx + 0.03, 0.4, 0.14, {0.7, 0.3, 0.4, 0.5});
    }
    return;
}
