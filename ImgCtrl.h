#ifndef IMGCTRL_DEF
#define IMGCTRL_DEF

#include "Image.h"
#include "Type.h"

namespace ImgCtrl{
    void InitImgCtrl();
    void ShowImg(int index, const char* img_fn, Vec2f pos, Vec2f rect);
    void KillImg(int index);
    void Render();
};

#endif
