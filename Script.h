#ifndef SCRIPT_DEF
#define SCRIPT_DEF

#include "inc_py.h"
#include <mutex>

class Script{
public:
    Script(const char* filename, const char* class_name);
    PyObject* GetAttribute(const char* name);
    void Shell();

private:

    std::mutex run_lock;

    PyObject* p_module;
    PyObject* p_class;
    PyObject* p_inst;
    PyObject* p_func;
    PyObject* p_obj;
};

#endif
