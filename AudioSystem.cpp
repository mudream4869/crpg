#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include "AudioSystem.h"

#include "audioloader/audioloader.h"

std::map<const char*, int, StrComp> AudioSystem::se_sound;

// device init
// will check for sounds/SE/__init__.ini

ALCdevice* AudioSystem::dev;
ALCcontext* AudioSystem::ctx;

ALuint AudioSystem::bgm_source;
ALuint AudioSystem::se_source;

bool AudioSystem::is_play_bgm;

ALuint AudioSystem::bgm_buffer;
std::vector<ALuint> AudioSystem::se_buffer;

char AudioSystem::certain_bgm[20];

void AudioSystem::InitAudioSystem(){
    
    is_play_bgm = false;
    certain_bgm[0] = 0;
 
    ALCdevice* dev = alcOpenDevice(NULL);
    ALCcontext* ctx = alcCreateContext(dev, NULL);
    alcMakeContextCurrent(ctx); 

    ALfloat source0Pos[]={ -2.0, 0.0, 0.0};
    ALfloat source0Vel[]={ 0.0, 0.0, 0.0}; 
    ALfloat listenerPos[]={0.0,0.0,4.0};
    ALfloat listenerVel[]={0.0,0.0,0.0};
    ALfloat listenerOri[]={0.0,0.0,1.0, 0.0,1.0,0.0};
    
    alListenerfv(AL_POSITION,listenerPos);
    alListenerfv(AL_VELOCITY,listenerVel);
    alListenerfv(AL_ORIENTATION,listenerOri);
    
    alGenSources(1, &bgm_source);
    alGenSources(1, &se_source);
    
    alSourcef(se_source, AL_PITCH, 1.0f);
    alSourcef(se_source, AL_GAIN, 1.0f);
    alSourcefv(se_source, AL_POSITION, source0Pos);
    alSourcefv(se_source, AL_VELOCITY, source0Vel);
    
    alSourcef(bgm_source, AL_PITCH, 1.0f);
    alSourcef(bgm_source, AL_GAIN, 1.0f);
    alSourcefv(bgm_source, AL_POSITION, source0Pos);
    alSourcefv(bgm_source, AL_VELOCITY, source0Vel);
    
    // Preload SE
    std::vector<std::string> get_se_list = GetFileUnderDir("sounds/SE");
    for(int lx = 0;lx < get_se_list.size();lx++){
        char sfn[20], fn[40];
        strcpy(sfn, get_se_list[lx].c_str());
        sprintf(fn, "sounds/SE/%s", sfn);
        AudioFileData get_info = LoadAudioFile(fn);
        if(get_info.isok){
            char* tmp_fn = new char[strlen(fn) + 2];
            strcpy(tmp_fn, fn);
            se_sound[tmp_fn] = (int)se_buffer.size();
            se_buffer.push_back(get_info.buffer);
        }
    }
    return;
}

// use atexit
void AudioSystem::ExitAudioSystem(){
    alcMakeContextCurrent(NULL);
    alcDestroyContext(ctx);
    alcCloseDevice(dev);
    return;
}

// BGM: Background Music for short
void AudioSystem::PlayBGM(const char* bgm_name){
    if(strcmp(bgm_name, certain_bgm) == 0)
        return;
    strcpy(certain_bgm, bgm_name);
    if(is_play_bgm){
        alDeleteBuffers(1, &bgm_buffer);
    }
    char full_bgm_name[40];
    sprintf(full_bgm_name, "sounds/BGM/%s", bgm_name);
    AudioFileData get_info = LoadAudioFile(full_bgm_name);
    if(get_info.isok){
        alSourceStop(bgm_source);
        bgm_buffer = get_info.buffer;
        alSourcei(bgm_source, AL_BUFFER, get_info.buffer);
        alSourcePlay(bgm_source);
    }
    return;
}

void AudioSystem::StopBGM(){
    if(is_play_bgm){
        alDeleteBuffers(1, &bgm_buffer);
    }
    alSourceStop(bgm_source);
    strcpy(certain_bgm, "");
    return;
}

// SE: Sound Effect for short
void AudioSystem::PlaySE(const char* se_name){
    auto se_buffer_index = (se_buffer[se_sound[se_name]]);
    alSourceStop(se_source);
    alSourcei(se_source, AL_BUFFER, se_buffer_index);
    alSourcePlay(se_source);
    return;
}
