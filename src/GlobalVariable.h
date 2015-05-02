#ifndef GLOBAL_VARIABLE_DEF
#define GLOBAL_VARIABLE_DEF

#include <vector>
#include <utility>
#include <string>


namespace GlobalVariable{
    void InitGlobalVariable();
    int GetValue(const char* name);
    void SetValue(const char* name, int a);
    std::vector< std::pair< std::string, int> > DumpValues();
    void ClearValue();

    bool GetFlag(const char* name);
    void SetFlag(const char* name, bool a);
    std::vector< std::pair< std::string, bool> > DumpFlags();
    void ClearFlag();
};

#endif
