#ifndef SYSCALL_DEF
#define SYSCALL_DEF

#include "inc_py.h"
#include <mutex>
#include <functional>
#include <queue>

namespace Sys{
    void InitSys();
    
    extern std::mutex func_lock;
    extern std::queue< std::function<void()> > func_que;
    void PushFunc(std::function<void()>);
    void DoFunc();
    
    PyObject* SysCall(PyObject* self, PyObject* para);
};

#endif
