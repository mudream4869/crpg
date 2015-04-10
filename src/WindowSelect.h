#ifndef WINDOWSELECT_DEF
#define WINDOWSELECT_DEF

#include <functional>
#include <vector>
#include <cwchar>
#include <string>
#include "Window.h"
#include "SysCall.h"
#include "Type.h"

class WindowSelect : public Window{
public:
    WindowSelect(float _left, float _top, float _width, float _height,
                std::function<void(int)> choose, std::function<void(int)> change,
                std::vector<std::wstring> _items);
    ~WindowSelect(); 
    void InputEvent(Input inp);
    void Update();

private:
    void ReDraw();
    int select_index;
    std::vector<std::wstring> items;
    std::function<void(int)> choose_callback;
    std::function<void(int)> change_callback;
};

#endif
