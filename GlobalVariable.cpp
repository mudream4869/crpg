#include <cstdlib>
#include <cstring>
#include "GlobalVariable.h"

std::map<const char*, int, StrCompare> GlobalVariable::global_value;
std::map<const char*, bool, StrCompare> GlobalVariable::global_flag;

void GlobalVariable::InitGlobalVariable(){
    return;
} 

int GlobalVariable::GetValue(const char* name){
    if(global_value.count(name) == 0){
        char* str = new char[strlen(name) + 2];
        strcpy(str, name);
        global_value[str] = 0;
    }
    return global_value[name];
}

void GlobalVariable::SetValue(const char* name, int a){
    if(global_value.count(name) == 0){
        char* str = new char[strlen(name) + 2];
        strcpy(str, name);
        global_value[str] = 0;
    }
    global_value[name] = a;
    return;
}

void GlobalVariable::ClearValue(){
    global_value.clear();
    return;
}

bool GlobalVariable::GetFlag(const char* name){
    if(global_flag.count(name) == 0){
        char* str = new char[strlen(name) + 2];
        strcpy(str, name);
        global_flag[str] = false;
    }
    return global_flag[name];
}

void GlobalVariable::SetFlag(const char* name, bool a){
    if(global_flag.count(name)){
        char* str = new char[strlen(name) + 1];
        strcpy(str, name);
        global_flag[str] = false;
    }
    global_flag[name] = a;
    return;
}

void GlobalVariable::ClearFlag(){
    global_flag.clear();
    return;
}
