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
};

#endif
