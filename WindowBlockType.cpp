#include "WindowBlockType.h"

WindowBlockType::WindowBlockType(float _left, float _top, float _width, float _height)
                :Window(_left, _top, _width, _height){}

bool WindowBlockType::IsOk() const {
    return true;
}

WriteType WindowBlockType::GetValue(){
    return {0, 0, ""};
};


