#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#elif _WIN32 || __FreeBSD__ || __linux
#include <AL/al.h> 
#include <AL/alc.h>
#endif
