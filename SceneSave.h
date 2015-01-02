#ifndef SCENESAVE_DEF
#define SCENESAVE_DEF

#include "Scene.h"
#include "Window.h"

class SceneSave : public Scene{
public:
    SceneSave();
    void InputEvent(Input inp);
    //void TickEvent(int delta_time);
    void Render();
private:
    Window* win_select;
    Window* win_show;
};


#endif
