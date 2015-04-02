#ifndef GRAPHICCOMPONENT_DEF
#define GRAPHICCOMPONENT_DEF

#include "Object.h"

class GraphicComponent{
public:
    GraphicComponent(Object* _obj);  
    void Render(float left, float top);
private:
    Object* obj;
    Vec2i walk_pos[4][4];
};

#endif
