#ifndef SCENE_DEF
#define SCENE_DEF

#include "Type.h"

class Scene{
public:
    Scene(float screen_width, float screen_height);
    virtual void InputEvent(Input inp);
    virtual void TickEvent(int delta_time);
    virtual void Render();

protected:
    float screen_width, screen_height;
};

#endif
