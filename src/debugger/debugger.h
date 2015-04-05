#ifndef DEBUGGER_DEF
#define DEBUGGER_DEF

#include <cstdarg>
#include <string>
#include "../inc_py.h"

namespace Debugger{
    void Init();
    void Print(const char*, ... );
    void Print(std::string);
    void Print(PyObject*);
    void PrintPyErr();
    void CheckPyObject(PyObject*, const char*, ... );
};

#endif 
