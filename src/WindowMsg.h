#ifndef WINDOW_MSG_DEF
#define WINDOW_MSG_DEF

//#include <condition_variable>
#include <cwchar>
#include "WindowBlockType.h"

class WindowMsg : public WindowBlockType{
public:
    WindowMsg(const wchar_t* str); 
    ~WindowMsg();
    void TickEvent(int a);
    void InputEvent(Input inp);
    //std::condition_variable* GetSignal();

private:
    int ptr;
    wchar_t* msg;
    //std::condition_variable cv;
};

#endif
