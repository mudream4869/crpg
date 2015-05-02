#ifndef TOOL_DEF
#define TOOL_DEF

#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>

std::vector<std::string> GetFileUnderDir(const char* dir_name);

char* GetFileName(char* path);

char* GetFileNameExt(char* filename);

struct StrComp{
    bool operator()(const char* str1, const char* str2) const {
        return strcmp(str1, str2) < 0;
    }
};

#endif
