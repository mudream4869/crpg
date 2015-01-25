#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include "AudioSystem.h"

std::map<const char*, int, StrCompare> AudioSystem::se_sound;

// device init
// will check for sounds/SE/__init__.ini

ALCdevice* AudioSystem::dev;
ALCcontext* AudioSystem::ctx;

ALuint AudioSystem::bgm_source;
ALuint AudioSystem::se_source;

bool AudioSystem::is_play_bgm;

ALuint AudioSystem::bgm_buffer;
std::vector<ALuint*> AudioSystem::se_buffer;

char AudioSystem::certain_bgm[20];

struct RIFF_Header {
    char chunkID[4];
    int chunkSize;//size not including chunkSize or chunkID
    char format[4];
};

struct WAVE_Format {
    char subChunkID[4];
    int subChunkSize;
    short audioFormat;
    short numChannels;
    int sampleRate;
    int byteRate;
    short blockAlign;
    short bitsPerSample;
};

struct WAVE_Data {
    char subChunkID[4]; //should contain the word data
    int subChunk2Size; //Stores the size of the data block
};

void CheckError(int op = -1, int _err = 0){
    int err;
    if(op == -1)
        err = alGetError(); // clear any error messages
    else 
        err = _err;
    if(err != AL_NO_ERROR){
        if(err == AL_INVALID_NAME)
            fprintf(stderr, "Error : Invalid Name\n");
        else if(err == AL_INVALID_ENUM)
            fprintf(stderr, "Error : Invalid Enum\n");
        else if(err == AL_INVALID_VALUE)
            fprintf(stderr, "Error : Invalid Value\n");
        else if(err == AL_INVALID_OPERATION)
            fprintf(stderr, "Error : Invalid Operation\n");
        else if(err == AL_OUT_OF_MEMORY)
            fprintf(stderr, "Error : Out of Memory\n");
        exit(1);
    }
    return;
}

bool _strcmp(const char* base, const char* cp){
    for(int lx = 0; base[lx] != 0;lx++){
        if(cp[lx] != base[lx])
            return false;
    }
    return true;
}

bool LoadWavFile(const char* filename, ALuint* buffer,
        ALsizei* size, ALsizei* frequency,
        ALenum* format) {
    //Local Declarations
    fprintf(stderr, "[1] filename = %s\n", filename);
    FILE* soundFile = NULL;
    WAVE_Format wave_format;
    RIFF_Header riff_header;
    WAVE_Data wave_data;
    unsigned char* data = 0;

    try{
        soundFile = fopen(filename, "rb");
        if (!soundFile)
            throw (filename);

        // Read in the first chunk into the struct
        fread(&riff_header, sizeof(RIFF_Header), 1, soundFile);

        //check for RIFF and WAVE tag in memeory
        if (_strcmp("RIFF", riff_header.chunkID) == false or 
                _strcmp("WAVE", riff_header.format) == false)
            throw ("Invalid RIFF or WAVE Header");

        //Read in the 2nd chunk for the wave info
        fread(&wave_format, sizeof(WAVE_Format), 1, soundFile);
        //check for fmt tag in memory
        if(_strcmp("fmt ", wave_format.subChunkID) == false)
            throw ("Invalid Wave Format");

        //check for extra parameters;
        if (wave_format.subChunkSize > 16)
            fseek(soundFile, sizeof(short), SEEK_CUR);

        //Read in the the last byte of data before the sound file
        fread(&wave_data, sizeof(WAVE_Data), 1, soundFile);
        //check for data tag in memory
        if(_strcmp("data", wave_data.subChunkID) == false)
            throw ("Invalid data header");

        //Allocate memory for data
        data = new unsigned char[wave_data.subChunk2Size];

        // Read in the sound data into the soundData variable
        if (!fread(data, wave_data.subChunk2Size, 1, soundFile))
            throw ("error loading WAVE data into struct!");

        //Now we set the variables that we passed in with the
        //data from the structs
        *size = wave_data.subChunk2Size;
        *frequency = wave_format.sampleRate;
        //The format is worked out by looking at the number of
        //channels and the bits per sample.
        if(wave_format.numChannels == 1) {
            if(wave_format.bitsPerSample == 8 )
                *format = AL_FORMAT_MONO8;
            else if(wave_format.bitsPerSample == 16)
                *format = AL_FORMAT_MONO16;
        }else if(wave_format.numChannels == 2) {
            if(wave_format.bitsPerSample == 8 )
                *format = AL_FORMAT_STEREO8;
            else if(wave_format.bitsPerSample == 16)
                *format = AL_FORMAT_STEREO16;
        }
        //create our openAL buffer and check for success
        alGenBuffers(1, buffer);
        CheckError(); 
        //now we put our data into the openAL buffer and
        //check for success
        alBufferData(*buffer, *format, (void*)data, *size, *frequency);
        CheckError(); 
        //clean up and return true if successful
        fclose(soundFile);
        fprintf(stderr, "load ok\n");
        delete[] data;
        return true;
    }catch(const char* err){
        printf("Error Occur: %s\n", err);
        //our catch statement for if we throw a string
        //std::cout << error << std::endl; 
        //clean up memory if wave loading fails
        if(soundFile != NULL)
            fclose(soundFile);
        if(data)
            delete[] data;
        //return false to indicate the failure to load wave
        return false;
    }
}

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

    FILE* fp = fopen("sounds/SE/__init__.ini", "r");
    if(fp == NULL){
        fprintf(stderr, "sounds/SE/__init__.ini not found.\n");
    }else{
        char sfn[20];
        while(fscanf(fp, "%s", sfn) != EOF){
            char fn[40];
            sprintf(fn, "sounds/SE/%s", sfn);
            ALuint* buffer = new ALuint;
            ALsizei size, frequency;
            ALenum format;
            if(LoadWavFile(fn, buffer, &size, &frequency, &format)){
                char* tmp_fn = new char[strlen(fn) + 2];
                strcpy(tmp_fn, fn);
                se_sound[tmp_fn] = (int)se_buffer.size();
                se_buffer.push_back(buffer);
            }else{
                delete buffer;
            }
        }
    }
    return;
}

// use atexit
void AudioSystem::ExitAudioSystem(){
    alcMakeContextCurrent(NULL);
    alcDestroyContext(ctx);
    alcCloseDevice(dev);
    for(int lx = 0;lx < se_buffer.size();lx++)
        delete se_buffer[lx];
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
    ALsizei size, frequency;
    ALenum format;
    char full_bgm_name[40];
    sprintf(full_bgm_name, "sounds/BGM/%s", bgm_name);
    if(LoadWavFile(full_bgm_name, &bgm_buffer, &size, &frequency, &format)){
        alSourceStop(bgm_source);
        alSourcei(bgm_source, AL_BUFFER, bgm_buffer);
        alSourcePlay(bgm_source);
    }
    return;
}

void AudioSystem::StopBGM(){
    if(is_play_bgm){
        alDeleteBuffers(1, &bgm_buffer);
    }
    alSourceStop(bgm_source);
    return;
}

// SE: Sound Effect for short
void AudioSystem::PlaySE(const char* se_name){
    auto se_buffer_index = *(se_buffer[se_sound[se_name]]);
    alSourceStop(se_source);
    alSourcei(se_source, AL_BUFFER, se_buffer_index);
    alSourcePlay(se_source);
    return;
}
