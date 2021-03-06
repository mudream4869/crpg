#ifndef CONSTANT_DEF
#define CONSTANT_DEF

namespace Constant{
    const int DIR_NONE = -1;
    const int DIR_DOWN = 0;
    const int DIR_LEFT = 1;
    const int DIR_RIGHT = 2;
    const int DIR_UP = 3;
    
    /** The four firection */
    const int DIR_X[] = {0, -1, 1, 0};
    const int DIR_Y[] = {1, 0, 0, -1};
    
    /** The delta of Tile */
    const float DELTA_X = 0.2;
    const float DELTA_Y = 0.2;
     
    const float WINDOW_WIDTH = 2;
    const float WINDOW_HEIGHT = 2;
    
    /** The size of screen*/
    const int FULL_WIDTH_PIXEL = 600;
    const int FULL_HEIGHT_PIXEL = 600;
    
    /** The size of font */
    const int FONT_HEIGHT_PIXEL = 40;
};

#endif
