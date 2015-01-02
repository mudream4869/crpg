#ifndef WINDOWSELECT_DEF
#define WINDOWSELECT_DEF

#include <functional>
#include <vector>
#include "Window.h"
#include "SysCall.h"
#include "Type.h"

class WindowSelect : public Window{
public:
    WindowSelect(float _left, float _top, float _width, float _height,
                std::function<void(int)> choose, std::function<void(int)> change,
                char** _items, int itemcount);
    ~WindowSelect(); 
    void InputEvent(Input inp);
    void Update();

private:
    void ReDraw();
    int select_index;
    std::vector<char*> items;
    std::function<void(int)> choose_callback;
    std::function<void(int)> change_callback;
};

#endif
