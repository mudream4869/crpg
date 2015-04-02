#include "inc_gl.h"
#include "inc_py.h"
#include <cstdlib>
#include <cstring>

#include "Config.h"
#include "Loader.cpp"
#include "ImgCtrl.h"
#include "InputCtrl.h"

#include "WindowBlockType.h"
#include "Scene.h"

void NormalKeyDown(unsigned char key, int x, int y){
    InputCtrl::PressNormalKey(key);
    Input inp = {INPUT_NORMAL_KEY_DOWN, x, y, key, 0};
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
    Input inp = {INPUT_NORMAL_KEY_UP, x, y, key, 0};
    if(WindowBlockType::msg != nullptr){
        WindowBlockType::msg->InputEvent(inp);
    }else{
        Scene::scene_certain->InputEvent(inp);
    }
    glutPostRedisplay();
    return;
}

void SpecialKeyDown(int key, int x, int y){
    InputCtrl::PressSpecialKey(key);
    Input inp = {INPUT_SPECIAL_KEY_DOWN, x, y, 0, key};
    if(WindowBlockType::msg != nullptr){
        WindowBlockType::msg->InputEvent(inp);
    }else{
        Scene::scene_certain->InputEvent(inp);
    }
    glutPostRedisplay();
    return;
}

void SpecialKeyUp(int key, int x, int y){
    InputCtrl::FreeSpecialKey(key);
    Input inp = {INPUT_SPECIAL_KEY_UP, x, y, 0, key};
    if(WindowBlockType::msg != nullptr){
        WindowBlockType::msg->InputEvent(inp);
    }else{
        Scene::scene_certain->InputEvent(inp);
    }
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
    Sys::DoFunc();
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

// 調整目錄
#ifdef __APPLE__
    int ptr = -1;
    char cd_path[1000]; 
    strcpy(cd_path, argv[0]);
    for(int lx = 0;cd_path[lx] != 0;lx++)
        if(cd_path[lx] == '/')
            ptr = lx;
    if(ptr >= 0){
        cd_path[ptr] = 0;
        chdir(cd_path);
    }
#endif

    Config::InitConfig();
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow(Config::GAME_TITLE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA); 
 
    glutDisplayFunc(Display);

#ifdef __APPLE__
    glutWMCloseFunc(CloseFunc);
#endif

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
