#ifndef SYSCALL_DEF
#define SYSCALL_DEF

#include "inc_py.h"
#include <mutex>
#include "Env.h"

namespace Sys{
    void InitSys();
    extern std::mutex syscall_mutex;
    PyObject* SysCall(PyObject* self, PyObject* para);
};

#endif
