#ifndef WINDOWGAMEOBJECT_DEF
#define WINDOWGAMEOBJECT_DEF

#include "Window.h"

class WindowGameObject : public Window{
public:
    WindowGameObject(float left, float top);
    
    void InputEvent(Input inp);
    void Update();

private:

    int ptr;

};

#endif

