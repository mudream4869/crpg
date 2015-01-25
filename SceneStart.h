#ifndef SCENESTART_DEF
#define SCENESTART_DEF

#include "Scene.h"
#include "Window.h"

class SceneStart : public Scene{
public:
    SceneStart();
    void InputEvent(Input inp);
    void TickEvent(int delta_time);
    void Render();
    
    static void Call();
    static Scene* scene_start;

private:
    void UpdateSelectBox();
    int select_index;
    Window* select_box;
    Image* bg;
};

#endif 
