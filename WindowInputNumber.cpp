#include "WindowInputNumber.h"

WindowInputNumber::WindowInputNumber()
    :WindowBlockType(0.75, 0.91, 0.5, 0.18){
    ptr = 0;
    for(int lx = 0;lx < 4;lx++)
        arr[lx] = 0;
    Update();
    return; 
}

void WindowInputNumber::Update(){
    this->Clear();
    for(int lx = 0;lx < 4;lx++){
        if(lx == ptr)
            this->DrawBox(lx*0.1 + 0.05, 0.02, 0.1, 0.14, {0.8, 0.5, 0.5, 0.5});
        char str[3];
        sprintf(str, "%d", arr[lx]);
        this->DrawText(lx*0.1 + 0.08, 0.1, str);
    }
    return;
}
         
void WindowInputNumber::InputEvent(Input inp){
    if(inp.InputType != INPUT_KEYPRESS) return;
    if(inp.Key == 13){
        WindowBlockType::ret_value = {WRITE_INT, arr[0]*1000 + arr[1]*100 + arr[2]*10 + arr[3], ""};
        delete this;
        return;
    }
    if(inp.Key == 'a'){
        ptr--;
        if(ptr == -1)
            ptr = 3;
    }else if(inp.Key == 'd'){
        ptr++;
        if(ptr == 4)
            ptr = 0;
    }else if(inp.Key == 'w'){
        arr[ptr]++;
        if(arr[ptr] == 10)
            arr[ptr] = 0;
    }else if(inp.Key == 's'){
        arr[ptr]--;
        if(arr[ptr] == -1)
            arr[ptr] = 9;
    }
    this->Update();
    return;
}
