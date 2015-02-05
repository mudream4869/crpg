#ifndef SCENESAVE_DEF
#define SCENESAVE_DEF

#include <vector>

#include "Scene.h"
#include "Window.h"

class SceneSave : public Scene{
public:
    SceneSave();
    void InputEvent(Input inp);
    //void TickEvent(int delta_time);
    void Render();
    
    void Snap();

    static void Call();
    static SceneSave* scene_save;
    static unsigned char* snap_img; 

private:
    Window* win_select;
    Window* win_show;
    Window* win_title;
};


#endif
