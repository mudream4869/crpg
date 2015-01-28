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
