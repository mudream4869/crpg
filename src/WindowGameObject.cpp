#include "WindowGameObject.h"
#include "GameObject.h"

#include "AudioSystem.h"

#include "Constant.h"

WindowGameObject::WindowGameObject(float _left, float _top):
    Window(_left, _top, 0.58, 0.6){
    this->ptr = 0;
    this->Update();
    return;
}

void WindowGameObject::Update(){
    this->Clear();
    float ly = 0;
    int cnt = 0;
    auto get_counts = GameObjectData::DumpCounts();
    for(auto get_data : get_counts){ 
        Image* obj_img = GameObjectData::GetGameObjectImage(get_data.first.c_str());
        this->DrawText(0.10, 0.16*ly + 0.135, get_data.first.c_str());
        this->DrawImage(0.0, 0.16*ly + 0.07, 0.08, 0.08, obj_img);
        char tmp_count[20];
        sprintf(tmp_count, "%d", get_data.second);
        this->DrawText(0.45, 0.16*ly + 0.135, tmp_count);

        if(ptr == cnt)
            this->DrawBox(0.0,0.16*ly + 0.035, 0.55, 0.14, {0.7, 0.3, 0.4, 0.5});

        ly++, cnt++; 
    }
    return;
} 

void WindowGameObject::InputEvent(Input inp){
    bool up = false, down = false;
    if(inp.type == INPUT_NORMAL_KEY_DOWN){
        if(inp.normal_key == 13){
            auto get_counts = GameObjectData::DumpCounts();
            GameObjectData::CallGameObject(get_counts[ptr].first.c_str());
            return;
        }
    }
    int dir = Input2Dir(inp);
    bool change = false;
    if(dir == Constant::DIR_UP and ptr > 0){
        AudioSystem::PlaySE("packitem_switch.ogg");
        ptr--, change = true;
    }

    if(dir == Constant::DIR_DOWN and ptr+1 < GameObjectData::GetSize()){
        AudioSystem::PlaySE("packitem_switch.ogg");
        ptr++, change = true;
    }
    
    if(change)
        Update();
    return;
}
