#include <OpenGL/gl.h> 
#include <OpenGL/glu.h> 
#include <GLUT/glut.h>
#include <Python/Python.h>
#include <cstdlib>

#include "Config.h"
#include "Loader.cpp"
#include "ImgCtrl.h"
#include "InputCtrl.h"

#include "WindowBlockType.h"
#include "Scene.h"

// KeyBroad Cut
void NormalKeyDown(unsigned char key, int x, int y){
    //printf("Press[%d]\n", key);
    InputCtrl::PressNormalKey(key);

    Input inp;
    inp.InputType = INPUT_KEYPRESS;
    inp.Key = key;
    if(WindowBlockType::msg != nullptr){
        WindowBlockType::msg->InputEvent(inp);
    }else{
        Scene::scene_certain->InputEvent(inp);
    }
    glutPostRedisplay();
    return;
}

void NormalKeyUp(unsigned char key, int x, int y){
    InputCtrl::FreeNormalKey(key);
    glutPostRedisplay();
    return;
}

void SpecialKeyDown(int key, int x, int y){
    InputCtrl::PressSpecialKey(key);
    glutPostRedisplay();
    return;
}

void SpecialKeyUp(int key, int x, int y){
    InputCtrl::FreeSpecialKey(key);
    glutPostRedisplay();
    return;
}
void SystemTimer(int value){
    if(WindowBlockType::msg != nullptr){
        WindowBlockType::msg->TickEvent(1);
    }else{
        Scene::scene_certain->TickEvent(1);
    }
    glutPostRedisplay();
    glutTimerFunc(25, SystemTimer, 1);
    return;
}

void MaskTimer(int value){
    Mask::TickEvent(value);
    glutPostRedisplay();
    glutTimerFunc(12, MaskTimer, 1);
    return;
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    Scene::scene_certain->Render();
    if(WindowBlockType::msg != nullptr)
        WindowBlockType::msg->Render();
    ImgCtrl::Render(); 
    if(Mask::IsMasking())
        Mask::Render();
    glFlush();
    return; 
}

void CloseFunc(){
    exit(0);
}

int main(int argc, char* argv[])  
{

#ifdef DEBUG
    fprintf(stderr, "Enter debug mod\n");
#endif

    Config::InitConfig();
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow(Config::GAME_TITLE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA); 
 
    glutDisplayFunc(Display);
    glutWMCloseFunc(CloseFunc);
    glutTimerFunc(25, SystemTimer, 1);
    glutTimerFunc(12, MaskTimer, 1);
    
    glutKeyboardFunc(NormalKeyDown);
    glutKeyboardUpFunc(NormalKeyUp);
    glutSpecialFunc(SpecialKeyDown);
    glutSpecialUpFunc(SpecialKeyUp);

    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    InitResource();
    glutMainLoop();

    Py_Finalize();
    return 0;
}
