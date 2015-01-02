#ifndef SYSCALL_DEF
#define SYSCALL_DEF

#include <Python/Python.h>
#include "Env.h"

namespace Sys{
    void InitSys(); 
    PyObject* SysCall(PyObject* self, PyObject* para);
};

#endif
