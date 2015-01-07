#include "WindowGameObject.h"
#include "GameObject.h"

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
    for(auto get_data = GameObjectData::gameobject_count.begin();
             get_data != GameObjectData::gameobject_count.end();
             get_data++){
        auto obj_data = GameObjectData::gameobject_pool[get_data->first];
        this->DrawText(0.10, 0.16*ly + 0.135, obj_data.name);
        this->DrawImage(0.0, 0.16*ly + 0.07, 0.08, 0.08, obj_data.img);
        char tmp_count[20];
        sprintf(tmp_count, "%d", get_data->second);
        this->DrawText(0.45, 0.16*ly + 0.135, tmp_count);

        if(ptr == cnt)
            this->DrawBox(0.0,0.16*ly + 0.035, 0.55, 0.14, {0.7, 0.3, 0.4, 0.5});

        ly++, cnt++; 
    }
    return;
} 

void WindowGameObject::InputEvent(Input inp){
    if(inp.InputType != INPUT_KEYPRESS) return;
    fprintf(stderr, "Enter InputEvent\n");
    bool change = false;
    if(inp.Key == 'w' and ptr > 0)
        ptr--, change = true;

    if(inp.Key == 's' and ptr+1 < GameObjectData::gameobject_count.size())
        ptr++, change = true;

    if(change)
        Update();
    return;
}
