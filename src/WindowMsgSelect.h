#ifndef WINDOWMSGSELECT_DEF
#define WINDOWMSGSELECT_DEF

#include <vector>
#include <cwchar>
#include <string>
#include "WindowBlockType.h"

class WindowMsgSelect : public WindowBlockType{
public:
    WindowMsgSelect(std::vector<std::wstring>);
    ~WindowMsgSelect();
    void InputEvent(Input inp);
    void Update();

private:
    int ptr;
    std::vector<std::wstring> options;
};

#endif
