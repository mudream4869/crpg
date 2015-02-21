#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Tool.h"

// For GetFileUnderDir header
#if __APPLE__ || __FreeBSD__ || __linux 
#include <sys/types.h>
#include <dirent.h>
#elif __WIN32
#include <windows.h>
#endif
// ------


int Absi(int a){
    return (a < 0) ? (-a):a;
}

std::vector<std::string> GetFileUnderDir(const char* dir_name){
    std::vector<std::string> ret;

#if __APPLE__ || __FreeBSD__ || __linux 
    DIR* dp = opendir(dir_name);
    struct dirent* ep; 
    if(dp != NULL){
        while((ep = readdir(dp))){
            if(strcmp(ep->d_name, ".") == 0 or
               strcmp(ep->d_name, "..") == 0) continue;
            ret.push_back(std::string(ep->d_name));
        }
        closedir(dp);
    }else{
        fprintf(stderr, "Couldn't open the directory\n");
        exit(1);
    }
#elif __WIN32
    
    WIN32_FIND_DATA data;
    HANDLE hFind;
    char d_dir_name[100];
    sprintf(d_dir_name, "%s/*", dir_name);
    hFind = FindFirstFile(d_dir_name, &data);
    if (hFind == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Couldn't open the directory\n");
        exit(1);
    } 
    else{
        do{
            if(strcmp(data.cFileName, ".") == 0 or 
               strcmp(data.cFileName, "..") == 0) continue;
            ret.push_back(std::string(data.cFileName));
        }while(FindNextFile(hFind, &data));
        FindClose(hFind);
    }
#endif
    return ret;
}

char* GetFileName(char* path){
    int sl = strlen(path) - 1;
    for(;path[sl] != '/' and sl>0;sl--);
    if(path[sl] == '/')
        return path + sl + 1;
    else
        return path + sl;
}

char* GetFileNameExt(char* filename){
    int sl = strlen(filename);
    int rc = sl;
    for(;sl >= 0;sl--)
        if(filename[sl] == '.')
            rc = sl+1;
    return filename + rc;
}
 
