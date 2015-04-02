#ifndef WINDOWBLOCKTYPE
#define WINDOWBLOCKTYPE

#include "Window.h"
#include "Type.h"

class WindowBlockType : public Window{
public:
    WindowBlockType(float _left, float _top, float _width, float _height);
    ~WindowBlockType();

    static WindowBlockType* msg;
    static WriteType ret_value;
};

#endif
