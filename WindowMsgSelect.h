#ifndef WINDOWMSGSELECT_DEF
#define WINDOWMSGSELECT_DEF

#include <vector>
#include "WindowBlockType.h"

class WindowMsgSelect : public WindowBlockType{
public:
    WindowMsgSelect(char* _options[], int count);
    ~WindowMsgSelect();
    void InputEvent(Input inp);
    void Update();

private:
    int ptr;
    std::vector<char*> options;
};

#endif
