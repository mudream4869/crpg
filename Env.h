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

std::map<const char*, Event*, StrCompare>* EnvGetEventPool();
std::map<const char*, Map*, StrCompare>* EnvGetMapPool();
void EnvSetCertainScene(const char* scene_name);
Event* EnvGetEvent(const char* event_file);

Map* EnvGetMap(const char* map_name);
void EnvAddMap(const char* map_name, Map* map_pointer);

#endif
