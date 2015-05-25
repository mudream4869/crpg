#include <cstdlib>
#include <cstring>
#include <mutex>
#include <map>

#include "GlobalVariable.h"
#include "Tool.h"

using std::vector;
using std::string;
using std::pair;

static std::map<string, int> global_value;
static std::map<string, bool> global_flag;

static std::mutex lock;

void GlobalVariable::InitGlobalVariable(){
    return;
} 

int GlobalVariable::GetValue(string name){
    int ret_value;
    lock.lock();
    if(global_value.count(name) == 0)
        ret_value = 0;
    else
        ret_value = global_value[name];
    lock.unlock();
    return ret_value;
}

void GlobalVariable::SetValue(string name, int a){
    lock.lock();
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

bool GlobalVariable::GetFlag(string name){
    bool ret_value;
    lock.lock();
    if(global_flag.count(name) == 0)
        ret_value = false;
    else
        ret_value = global_flag[name];
    lock.unlock();
    return ret_value; 
}

void GlobalVariable::SetFlag(string name, bool a){
    lock.lock();
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
