#ifndef WINDOW_MSG_DEF
#define WINDOW_MSG_DEF

#include <condition_variable>

#include "Window.h"

class WindowMsg : public Window{
public:
    WindowMsg(float _left, float _top, float _width, float _height, const char* str); 
    ~WindowMsg();
    void TickEvent(int a);
    bool IsOk() const;
    std::condition_variable* GetSignal();

private:
    int ptr;
    char* msg;
    std::condition_variable cv;
};

#endif
