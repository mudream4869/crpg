#include <thread>
#include "Script.h"
#include "SysCall.h"
#include "PyLock.h"

#include "debugger/debugger.h"

Script::Script(std::string file_name, const char* class_name){
    char tmp[20];
    
    sprintf(tmp, "scripts.%s", file_name.c_str());
    PySys_SetPath(".");
    
    Debugger::Print("Loading from %s....\n", tmp);

    this->p_module = PyImport_ImportModule(tmp);

    Debugger::CheckPyObject(
        this->p_module,
        "Fail to import %s.\n", tmp 
    );

    Load(class_name);
    return;
}

Script::Script(PyObject* module, const char* class_name){
    this->p_module = module;
    Load(class_name);
    return;
}

void Script::Load(const char* class_name){


    this->p_class = PyObject_GetAttrString(p_module, class_name);

    Debugger::CheckPyObject(
        this->p_class,
        "Fail to get class '%s'.\n", class_name
    );

    PyMethodDef *callback = new PyMethodDef;

    callback->ml_name = "func";
    callback->ml_meth = Sys::SysCall;
    callback->ml_flags = 1;

    PyObject* pcb = PyCFunction_New(callback, NULL);
    PyObject* pArg = Py_BuildValue("(O)", pcb);
    this->p_inst = PyObject_CallObject(this->p_class, pArg);
    

    Debugger::CheckPyObject(
        this->p_inst,
        "Fail to get new instance of %s\n", class_name
    );

    this->p_func = PyObject_GetAttrString(this->p_inst, "Action");
    

    Debugger::CheckPyObject(
        this->p_func,
        "Fail to get 'Action' function from %s\n", class_name
    );

    return;
}

PyObject* Script::GetAttr(const char* attr_name){
    return PyObject_GetAttrString(this->p_inst, attr_name);
}

void Script::Shell(){
    if(run_lock.try_lock() == false)
        return;
    std::thread torun(
        [this]{
            fprintf(stderr, "=================\n");
            PyLock();
            auto state = Py_NewInterpreter(); 
            PyEval_RestoreThread(state);
            PyObject* pArg = Py_BuildValue("()");

#ifdef DEBUG
            PyErr_Clear();
#endif

            PyObject* ret = PyObject_CallObject(this->p_func, pArg);

#ifdef DEBUG
            if(PyErr_Occurred() != NULL){
                fprintf(stderr, "Script error\n");
                PyErr_Print();
                exit(1);
            }
#endif

            Py_XDECREF(pArg);
            Py_XDECREF(ret);
            PyUnlock();
            this->run_lock.unlock();
        }
    );
    torun.detach();
    return;
}
