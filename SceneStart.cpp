#include <cstdlib>
#include "SceneStart.h"
#include "Image.h"
#include "Env.h"

SceneStart::SceneStart(){ 
    select_box = new Window(0.7, 1, 0.6, 0.53);
    select_index = 0;
    //bg = new Image("startbg.bmp");
    UpdateSelectBox();
    return;
}

void SceneStart::UpdateSelectBox(){
    select_box->Clear();
    const char str[][10] = {"New Story", "Old Story", "Exit"};
    for(int lx = 0;lx < 3;lx++){
        if(lx == select_index)
            select_box->DrawBox(0.08, 0.16*lx + 0.03, 0.4, 0.14, {0.7, 0.3, 0.4, 0.5});
        select_box->DrawText(0.1, 0.16*lx + 0.135, str[lx]);
    }
    return;
}

void SceneStart::InputEvent(Input inp){
    bool change = false;
    if(inp.InputType == INPUT_KEYPRESS){
        if(inp.Key == 'w'){
            if(select_index > 0)
                select_index--, change = true;
        }else if(inp.Key == 's'){
            if(select_index < 2)
                select_index++, change = true;
        }else if(inp.Key == 13){
            if(select_index == 0){
                EnvSetCertainScene("scene_play");
            }else if(select_index == 1){
                EnvSetCertainScene("scene_load");
                return; 
            }else if(select_index == 2){
                exit(0);
            }
        }
    }
    if(change)
        UpdateSelectBox();
    return;
}

void SceneStart::TickEvent(int delta_time){
    return;
}

void SceneStart::Render(){
    //bg->TestRender(0, 0, screen_width, screen_height, 1);
    select_box->Render();
    return;
}
