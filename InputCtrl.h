#ifndef INPUTCTRL_DEF
#define INPUTCTRL_DEF

#include <OpenGL/gl.h> 
#include <OpenGL/glu.h> 
#include <GLUT/glut.h>
#include <set>

namespace InputCtrl{
    void Init();

    void PressSpecialKey(int key);
    void PressNormalKey(unsigned char key);

    void FreeSpecialKey(int key);
    void FreeNormalKey(unsigned char key);

    bool IsSpecialKeyPress(int key);
    bool IsNormalKeyPress(unsigned char key);
    
    const int ARROW_NONE = -1;
    const int ARROW_DOWN = 0;
    const int ARROW_LEFT = 1;
    const int ARROW_RIGHT = 2;
    const int ARROW_UP = 3;
    int GetArrowCommand();
};

#endif
