#ifndef GLOBAL_VARIABLE_DEF
#define GLOBAL_VARIABLE_DEF

#include <mutex>
#include "Env.h"

namespace GlobalVariable{
    extern std::map<const char*, int, StrCompare> global_value;
    extern std::map<const char*, bool, StrCompare> global_flag;
    
    extern std::mutex lock;

    void InitGlobalVariable();
    int GetValue(const char* name);
    void SetValue(const char* name, int a);
    void ClearValue();

    bool GetFlag(const char* name);
    void SetFlag(const char* name, bool a);
    void ClearFlag();
};

#endif
