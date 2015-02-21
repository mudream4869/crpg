#ifndef AUDIO_LOADER_INC
#define AUDIO_LOADER_INC

#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#elif _WIN32 || __FreeBSD__ || __linux
#include <AL/al.h> 
#include <AL/alc.h>
#endif


typedef struct __AudioFileData{
    bool isok;
    ALuint buffer;
}AudioFileData;

AudioFileData LoadWavFile(const char* filename);
AudioFileData LoadOggFile(const char* filename);

#endif
