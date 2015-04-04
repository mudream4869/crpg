#include "../../src/Tool.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <cassert>

struct AbsiTester{
    void Run(){
        assert(Absi(-5) == 5);
        assert(Absi(6) == 6);
        return;
    }
};

struct GetFileNameTester{
    void Run(){
        char path1[] = "C:/abc/def";
        char path2[] = "/tmp2/abc/def";
        char path3[] = "def";
        assert(strcmp(GetFileName(path1), "def") == 0);
        assert(strcmp(GetFileName(path2), "def") == 0);
        assert(strcmp(GetFileName(path3), "def") == 0);
        return;
    }
};

struct GetFileNameExtTester{
    void Run(){
        char path1[] = "C:/abc/1.def";
        char path2[] = "/tmp2/abc/2.de";
        char path3[] = "3";
        assert(strcmp(GetFileNameExt(path1), "def") == 0);
        assert(strcmp(GetFileNameExt(path2), "de") == 0);
        assert(strcmp(GetFileNameExt(path3), "") == 0);
        return;
    }
};

struct GetFileUnderDirTester{
    void Run(){
        std::vector<std::string> ans;
        ans.push_back("file1");
        ans.push_back("file2");
        ans.push_back("file3");
        auto respond = GetFileUnderDir("testfolder");
        std::sort(respond.begin(), respond.end());
        assert(respond == ans);
        return;
    }
};

int main(){
    (new AbsiTester)->Run();
    (new GetFileNameTester)->Run();
    (new GetFileNameExtTester)->Run();
    (new GetFileUnderDirTester)->Run();
    return 0;
}
