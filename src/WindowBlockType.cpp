#include "WindowBlockType.h"

WindowBlockType* WindowBlockType::msg = nullptr;
WriteType WindowBlockType::ret_value = {0, 0, ""};

WindowBlockType::WindowBlockType(float _left, float _top, float _width, float _height)
                :Window(_left, _top, _width, _height){}

WindowBlockType::~WindowBlockType(){
    WindowBlockType::msg = nullptr;
}
