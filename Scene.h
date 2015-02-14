#ifndef SCENE_DEF
#define SCENE_DEF

#include "Type.h"

class Scene{
public:
    Scene();
    virtual void InputEvent(Input inp);
    virtual void TickEvent(int delta_time);
    virtual void Render();
    virtual void Call();
    
    static Scene* scene_certain;
protected:
    float screen_width, screen_height;
};

#endif
