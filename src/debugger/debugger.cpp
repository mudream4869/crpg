#include <cstdio>
#include <cstdlib>
#include "debugger.h"

static FILE* write_file; 

void Debugger::Init(){
    write_file = stderr;
#ifdef DEBUG
    Debugger::Print("Enter debug mod\n");
#endif
    return;
}

void Debugger::Print(const char* format, ... ){
#ifdef DEBUG
    char buffer[256];
    va_list args;
    va_start (args, format);
    vsprintf (buffer,format, args);
    perror (buffer);
    va_end (args);
    fprintf(write_file, "%s", buffer);
#endif
    return;
}

void Debugger::Print(std::string str){
#ifdef DEBUG
    fprintf(write_file, "%s", str.c_str());
#endif
    return;
}

void Debugger::Print(PyObject* obj){
#ifdef DEBUG
    PyObject_Print(obj, write_file, 0);
#endif
    return;
}

void Debugger::PrintPyErr(){
#ifdef DEBUG
    PyErr_Print();
#endif
    return;
}

void Debugger::CheckPyObject(PyObject* obj , const char* format, ... ){
#ifdef DEBUG
    if(obj == NULL){
        char buffer[256];
        va_list args;
        va_start (args, format);
        vsprintf (buffer,format, args);
        perror (buffer);
        va_end (args);
        fprintf(write_file, "%s", buffer);
        PyErr_Print();
        exit(1);
    }
#endif
    return;
}
