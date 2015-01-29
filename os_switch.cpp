/* Only support for Windows and Mac */
#include <cstdio>
int main() {
#ifdef __APPLE__
    printf("apple");
#elif _WIN32
    printf("win32");
#else
    printf("err");
#endif
    return 0;
}
