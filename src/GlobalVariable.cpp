#include <cstdlib>
#include <cstring>
#include <mutex>
#include <map>

#include "GlobalVariable.h"
#include "Tool.h"

using std::vector;
using std::string;
using std::pair;

static std::map<const char*, int, StrComp> global_value;
static std::map<const char*, bool, StrComp> global_flag;

static std::mutex lock;

void GlobalVariable::InitGlobalVariable(){
    return;
} 

int GlobalVariable::GetValue(const char* name){
    int ret_value;
    lock.lock();
    if(global_value.count(name) == 0)
        ret_value = 0;
    else
        ret_value = global_value[name];
    lock.unlock();
    return ret_value;
}

void GlobalVariable::SetValue(const char* name, int a){
    lock.lock();
    if(global_value.count(name) == 0){
        char* str = new char[strlen(name) + 2];
        strcpy(str, name);
        global_value[str] = 0;
    }
    global_value[name] = a;
    lock.unlock();
    return;
}

vector< pair<string, int> > GlobalVariable::DumpValues(){
    vector< pair<string, int> > ret;
    for(auto& it : global_value)
        ret.push_back(pair<string,int>(it.first, it.second));
    return ret;
}

void GlobalVariable::ClearValue(){
    lock.lock();
    global_value.clear();
    lock.unlock();
    return;
}

bool GlobalVariable::GetFlag(const char* name){
    bool ret_value;
    lock.lock();
    if(global_flag.count(name) == 0)
        ret_value = false;
    else
        ret_value = global_flag[name];
    lock.unlock();
    return ret_value; 
}

void GlobalVariable::SetFlag(const char* name, bool a){
    lock.lock();
    if(global_flag.count(name) == 0){
        char* str = new char[strlen(name) + 2];
        strcpy(str, name);
        global_flag[str] = false;
    }
    global_flag[name] = a;
    lock.unlock();
    return;
}

vector< pair<string, bool> > GlobalVariable::DumpFlags(){
    vector< pair<string, bool> > ret;
    for(auto& it : global_flag)
        ret.push_back(pair<string,int>(it.first, it.second));
    return ret;
}

void GlobalVariable::ClearFlag(){
    lock.lock();
    global_flag.clear();
    lock.unlock();
    return;
}
