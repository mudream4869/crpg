#include <cstring>
#include <cstdlib>
#include "Env.h"
#include "Scene.h"
#include "SysCall.h"

Env* env;

void EnvInit(){
    env = new Env;
    return;
}

void EnvInsert(const char* str, void* inp){
    char* ss = new char[strlen(str) + 2];
    strcpy(ss, str);
    env->operator[](ss) = inp;
    return;
}

void* EnvGet(const char* str){
    return env->operator[](str);
}

int EnvCount(const char* str){
    return env->count(str);
}
