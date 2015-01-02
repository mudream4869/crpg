#ifndef WINDOW_MSG_DEF
#define WINDOW_MSG_DEF

#include "Window.h"
class WindowMsg : public Window{
public:
    WindowMsg(float _left, float _top, float _width, float _height, const char* str); 
    void TickEvent(int a);
    bool IsOk() const;
private:
    int ptr;
    float ptr_x, ptr_y;
    char* msg;
    bool isok;
};

#endif
