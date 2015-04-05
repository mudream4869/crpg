#ifndef GLOBAL_VARIABLE_DEF
#define GLOBAL_VARIABLE_DEF

#include <vector>
#include <utility>
#include <string>

using std::vector;
using std::string;
using std::pair;

namespace GlobalVariable{
    void InitGlobalVariable();
    int GetValue(const char* name);
    void SetValue(const char* name, int a);
    vector< pair<string, int> > DumpValues();
    void ClearValue();

    bool GetFlag(const char* name);
    void SetFlag(const char* name, bool a);
    vector< pair<string, bool> > DumpFlags();
    void ClearFlag();
};

#endif
