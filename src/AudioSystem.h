#ifndef AUDIO_DEF
#define AUDIO_DEF

namespace AudioSystem{
    //will check for sounds/BGM/__init__.ini, sounds/SE/__init__.ini
    void InitAudioSystem();
    void ExitAudioSystem();
    
    // BGM: Background Music for short
    void PlayBGM(const char*);
    void StopBGM();

    // SE: Sound Effect for short
    void PlaySE(const char*);

};

#endif 
