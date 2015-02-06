#ifndef ENV_INC
#define ENV_INC

#include <functional>
#include <cstring>
#include <map>

#include "Event.h"
#include "Map.h"

struct StrCompare : public std::binary_function<const char*, const char*, bool>{
    public:
        bool operator() (const char* str1, const char* str2) const
            { return std::strcmp(str1, str2) < 0; }
};
typedef std::map<const char*, void* , StrCompare> Env;

extern Env* env;
void EnvInit();

void EnvInsert(const char* str, void* inp);
void* EnvGet(const char* str);
int EnvCount(const char* str);

#endif
