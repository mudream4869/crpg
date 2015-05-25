#ifndef TOOL_DEF
#define TOOL_DEF

#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>

/**
 *  @brief Get files list under directory
 *  @param
 *      dir_name: directory name 
 *  @return 
 *      [filename]
 */
std::vector<std::string> GetFileUnderDir(const char* dir_name);

/**
 *  @brief Get filename in file path
 *  @param
 *      path: file path with filename
 *  @return
 *      only filename
 */
char* GetFileName(char* path);

/**
 *  @brief Get filename extension
 *  @param
 *      filename: File name
 *  @return
 *      filename Extension
 */
char* GetFileNameExt(char* filename);

struct StrComp{
    bool operator()(const char* str1, const char* str2) const {
        return strcmp(str1, str2) < 0;
    }
};

#endif
