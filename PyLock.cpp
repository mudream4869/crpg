#include <mutex>
#include "PyLock.h"

static std::mutex mut;

void PyLock(){
    mut.lock();
    return;
}

void PyUnlock(){
    mut.unlock();
    return;
}

std::mutex& PyGetMutex(){
    return mut;
}
