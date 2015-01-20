#ifndef MASK_DEF
#define MASK_DEF

#include "Type.h"

namespace Mask{
    void InitMask();
    void SetMask(Color4f st, Color4f ed, int time);
    void TickEvent(int a);
    void Render();
    bool IsMasking();
    void Clear();
};

#endif
