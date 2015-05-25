#include <cstdio>
#include <cstdlib>
#include "debugger.h"

using std::string;

static FILE* write_file = nullptr;

void Debugger::Init(){
    write_file = stderr;
#ifdef DEBUG
    Debugger::Print("Enter debug mod\n");
#endif
    return;
}

void Debugger::Print(const char* format, ... ){
#ifdef DEBUG
    va_list args;
    va_start(args, format);
    vfprintf(write_file, format, args);
    va_end(args);
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

void PrintFatal(std::string from, std::string msg){
    printf("[Fatal] From %s : %s\n", from.c_str(), msg.c_str());
    return;
}

void PrintError(std::string from, std::string msg){
    printf("[Error] From %s : %s\n", from.c_str(), msg.c_str());
    return;
}

void PrintWarning(std::string from, std::string msg){
    printf("[Warning] From %s : %s\n", from.c_str(), msg.c_str());
    return;
}
