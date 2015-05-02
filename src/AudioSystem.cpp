#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <map>

#include "inc_al.h"
#include "AudioSystem.h"
#include "Config.h"
#include "Tool.h"

#include "audioloader/audioloader.h"

static std::map<std::string, int> se_sound;

// device init
// will check for sounds/SE/__init__.ini

static ALCdevice* dev;
static ALCcontext* ctx;

static ALuint bgm_source;
static ALuint se_source;

static bool is_play_bgm;

static ALuint bgm_buffer;
static std::vector<ALuint> se_buffer;

static std::string certain_bgm;

void AudioSystem::InitAudioSystem(){
    
    is_play_bgm = false;
 
    dev = alcOpenDevice(NULL);
    ctx = alcCreateContext(dev, NULL);
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
    std::vector<std::string> get_se_list = GetFileUnderDir(Config::PATH_SOUND_SEFILE);
    for(int lx = 0;lx < get_se_list.size();lx++){
        char fn[40];
        std::string& sfn = get_se_list[lx];
        sprintf(fn, "%s/%s", Config::PATH_SOUND_SEFILE, sfn.c_str());
        AudioFileData get_info = LoadAudioFile(fn);
        if(get_info.isok){
            se_sound[sfn] = (int)se_buffer.size();
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
void AudioSystem::PlayBGM(std::string bgm_name){
    if(bgm_name == certain_bgm)
        return;
    certain_bgm = bgm_name;
    if(is_play_bgm){
        alDeleteBuffers(1, &bgm_buffer);
    }
    char full_bgm_name[40];
    sprintf(full_bgm_name, "%s/%s", Config::PATH_SOUND_BGMFILE, bgm_name.c_str());
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
    certain_bgm = "";
    return;
}

// SE: Sound Effect for short
void AudioSystem::PlaySE(std::string se_name){
    auto se_buffer_index = (se_buffer[se_sound[se_name]]);
    alSourceStop(se_source);
    alSourcei(se_source, AL_BUFFER, se_buffer_index);
    alSourcePlay(se_source);
    return;
}
