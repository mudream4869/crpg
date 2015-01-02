#include "WindowSelect.h"

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
    fprintf(stderr, "ready to update\n");
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
    if(inp.InputType != INPUT_KEYPRESS) return;
    if(inp.Key == 27)
        choose_callback(-1);
    if(inp.Key == 'w' and select_index > 0){
        select_index--;
        this->Update();
    }
    if(inp.Key == 's' and select_index+1 < items.size()){
        select_index++;
        this->Update();
    }
    if(inp.Key == 13)
        choose_callback(select_index);
        
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
