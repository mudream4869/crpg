#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Tool.h"

int Absi(int a){
    return (a < 0) ? (-a):a;
}

/*namespace fs = boost::filesystem;
std::vector<std::string> GetTmx(const char* dir_name){
    std::vector<std::string> ret;
    char full_dir_name[20];
    sprintf(full_dir_name, "%s/", dir_name);
    fs::path directory(full_dir_name);
    fs::directory_iterator iter(directory), end;
    for(;iter != end; ++iter)
        if (iter->path().extension() == ".tmx"){
            ret.push_back(iter->path().filename().string());
            fprintf("[%s]\n", iter->path().filename().string().c_str());
        }
    return ret;
}*/

char* GetFileName(char* path){
    int sl = strlen(path) - 1;
    for(;path[sl] != '/' and sl>0;sl--);
    if(path[sl] == '/')
        return path + sl + 1;
    else
        return path + sl;
}
