#ifndef WINDOWGAMEOBJECT_DEF
#define WINDOWGAMEOBJECT_DEF

#include "Window.h"

class WindowGameObject : public Window{
public:
    WindowGameObject(float left, float top);
    
    void InputEvent(Input inp);

private:

    void Update();
    int ptr;

};

#endif

