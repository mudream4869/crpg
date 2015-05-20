#ifndef IMGCTRL_DEF
#define IMGCTRL_DEF

#include "Type.h"

namespace ImgCtrl{

    /**
     *  @brief Initialize the ImgCtrl's envirnment. 
     */
    void InitImgCtrl();

    /**
     *  @brief Show a image
     *  @param
     *      index: the index that want to use
     *      img_fn: the filename of image
     *      pos: the position of image
     *      rect: the size of image
     */
    void ShowImg(int index, const char* img_fn, Vec2f pos, Vec2f rect);

    /**
     *  @brief Remove a image
     *  @param 
     *      index: the image' index
     */
    void KillImg(int index);

    /**
     *  @brief Render all image
     *         should be call at Display
     */
    void Render();
};

#endif
