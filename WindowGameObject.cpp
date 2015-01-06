#include "WindowGameObject.h"
#include "GameObject.h"

WindowGameObject::WindowGameObject(float _left, float _top):
    Window(_left, _top, 0.5, 0.5){
    this->ptr = 0;
    this->Update();
    return;
}

void WindowGameObject::Update(){
    this->Clear();
    float ly = 0.05;
    int cnt = 0;
    for(auto get_data = GameObjectData::gameobject_count.begin();
             get_data != GameObjectData::gameobject_count.end();
             get_data++){
        auto obj_data = GameObjectData::gameobject_pool[get_data->first];
        this->DrawText(0.05, ly, obj_data.name);
        char tmp_count[20];
        sprintf(tmp_count, "%d", get_data->second);
        this->DrawText(0.3, ly, tmp_count);
        
        if(ptr == cnt){
            this->DrawBox(
                0.05, ly, 0.05, 0.4, {125, 125, 125, 125}
            );
        }
        ly += 0.05, cnt++; 
    }
    return;
} 

void WindowGameObject::InputEvent(Input inp){
    if(inp.InputType != INPUT_KEYPRESS) return;
    bool change = false;
    if(inp.Key == 'w' and ptr > 0)
        ptr--, change = true;

    if(inp.Key == 's' and ptr+1 < GameObjectData::gameobject_count.size())
        ptr++, change = true;

    if(change)
        Update();
    return;
}
