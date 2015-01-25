#ifndef WINDOWINPUTNUMBER_DEF
#define WINDOWINPUTNUMBER_DEF

#include "WindowBlockType.h"

class WindowInputNumber : public WindowBlockType{
public:
    WindowInputNumber();
    void InputEvent(Input inp);
    void Update();
private:
    int arr[4];
    int ptr;
};

#endif
