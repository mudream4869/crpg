#include <thread>
#include "Script.h"
#include "SysCall.h"
#include "PyLock.h"

Script::Script(const char* file_name, const char* class_name){
    char tmp[20];
    
    sprintf(tmp, "scripts.%s", file_name);
    PySys_SetPath(".");
    
#ifdef DEBUG 
    fprintf(stderr, "Loading from %s....\n", tmp);
#endif

    this->p_module = PyImport_ImportModule(tmp);

#ifdef DEBUG
    if(this->p_module == NULL){
        fprintf(stderr, "Fail to import %s.\n", tmp);
        PyErr_Print();
        exit(1);
    }
#endif

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

#ifdef DEBUG
    if(this->p_class == NULL){
        fprintf(stderr, "Fail to get class '%s'.\n", class_name);
        PyErr_Print();
        exit(1);
    }
#endif

    PyMethodDef *callback = new PyMethodDef;

    callback->ml_name = "func";
    callback->ml_meth = Sys::SysCall;
    callback->ml_flags = 1;

    PyObject* pcb = PyCFunction_New(callback, NULL);
    PyObject* pArg = Py_BuildValue("(O)", pcb);
    this->p_inst = PyObject_CallObject(this->p_class, pArg);

#ifdef DEBUG
    if(this->p_inst == NULL){
        fprintf(stderr, "Fail to get new instance of %s\n", class_name);
        PyErr_Print();
        exit(1);
    }
#endif

    this->p_func = PyObject_GetAttrString(this->p_inst, "Action");

#ifdef DEBUG
    if(this->p_func == NULL){
        fprintf(stderr, "Fail to get 'Action' function from %s\n", class_name);
        PyErr_Print();
        exit(1);
    }
#endif

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
