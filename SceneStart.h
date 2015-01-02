#ifndef SCENESTART_DEF
#define SCENESTART_DEF

#include "Scene.h"
#include "Window.h"

class SceneStart : public Scene{
public:
    SceneStart(float _screen_width, float _screen_height);
    void InputEvent(Input inp);
    void TickEvent(int delta_time);
    void Render();

private:
    void UpdateSelectBox();
    int select_index;
    Window* select_box;
    Image* bg;
};

#endif 
