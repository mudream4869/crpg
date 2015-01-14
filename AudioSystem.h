#ifndef AUDIO_DEF
#define AUDIO_DEF

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <vector>
#include "Env.h"

namespace AudioSystem{
    extern std::map<const char*, int, StrCompare> se_sound;
    extern ALCdevice* dev;
    extern ALCcontext* ctx;

    extern ALuint bgm_source;
    extern ALuint se_source;

    extern bool is_play_bgm;

    extern ALuint bgm_buffer;
    extern std::vector<ALuint*> se_buffer;


    //will check for sounds/BGM/__init__.ini, sounds/SE/__init__.ini
    void InitAudioSystem();
    void ExitAudioSystem();
    // BGM: Background Music for short
    void PlayBGM(const char*);

    // SE: Sound Effect for short
    void PlaySE(const char*);

};



#endif 
