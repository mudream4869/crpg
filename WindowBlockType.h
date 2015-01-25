#ifndef WINDOWBLOCKTYPE
#define WINDOWBLOCKTYPE

#include "Window.h"
#include "Type.h"

class WindowBlockType : public Window{
public:
    WindowBlockType(float _left, float _top, float _width, float _height);
    ~WindowBlockType();
    virtual bool IsOk() const;
    virtual WriteType GetValue();

    static WindowBlockType* msg;
};

#endif
