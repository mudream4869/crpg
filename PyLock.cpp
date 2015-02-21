#include <mutex>
#include <cstdio>
#include "PyLock.h"

static std::mutex mut;

void PyLock(){
    fprintf(stderr, "py ready lock.\n");
    mut.lock();
    fprintf(stderr, "py lock ok.\n");
    return;
}

void PyUnlock(){
    fprintf(stderr, "py ready to unlock\n");
    mut.unlock();
    fprintf(stderr, "py unlock ok\n");
    return;
}

std::mutex& PyGetMutex(){
    return mut;
}
