#ifndef SCENELOAD_DEF
#define SCENELOAD_DEF

#include "Scene.h"
#include "Window.h"

class SceneLoad : public Scene{
public:
    SceneLoad();
    void InputEvent(Input inp);
    //void TickEvent(int delta_time);
    void Render();
    
    static void Call();
    static Scene* scene_load;
private:
    Window* win_select;
    Window* win_show;
};


#endif
