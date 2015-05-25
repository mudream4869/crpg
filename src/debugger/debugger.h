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
   
    /**
     *  @brief Print Fatal msg
     *  @param
     *      from: class name
     *      msg: msg string
     */
    void PrintFatal(std::string from, std::string msg);

    /**
     *  @brief Print Error msg
     *  @param
     *      from: class name
     *      msg: msg string
     */
    void PrintError(std::string from, std::string msg);

    /**
     *  @brief Print Warning msg
     *  @param
     *      from: class name
     *      msg: msg string
     */
    void PrintWarning(std::string from, std::string msg);
};

#endif 
