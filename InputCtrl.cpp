#include <cstring>

#include "InputCtrl.h"

static std::set<int> special_key_table;
static bool normal_key_table[260] = {0};

void InputCtrl::Init(){
    return;
}

void InputCtrl::PressSpecialKey(int key){
    special_key_table.insert(key);
    return;
}

void InputCtrl::PressNormalKey(unsigned char key){
    normal_key_table[key] = true;
    return;
}

void InputCtrl::FreeSpecialKey(int key){
    special_key_table.erase(key);
    return;
}

void InputCtrl::FreeNormalKey(unsigned char key){
    normal_key_table[key] = false;
    return;
}

bool InputCtrl::IsSpecialKeyPress(int key){
    return special_key_table.count(key) > 0;
}

bool InputCtrl::IsNormalKeyPress(unsigned char key){
    return normal_key_table[key];
}

int InputCtrl::GetArrowCommand(){
    if(normal_key_table[(unsigned char)'a'] or special_key_table.count(GLUT_KEY_LEFT)) return ARROW_LEFT;
    if(normal_key_table[(unsigned char)'s'] or special_key_table.count(GLUT_KEY_DOWN)) return ARROW_DOWN;
    if(normal_key_table[(unsigned char)'w'] or special_key_table.count(GLUT_KEY_UP)) return ARROW_UP;
    if(normal_key_table[(unsigned char)'d'] or special_key_table.count(GLUT_KEY_RIGHT)) return ARROW_RIGHT;
    return ARROW_NONE;
}
