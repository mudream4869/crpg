#ifndef AUDIO_DEF
#define AUDIO_DEF

#include <string>

namespace AudioSystem{
    void InitAudioSystem();
    void ExitAudioSystem();
    
    // BGM: Background Music for short
    void PlayBGM(std::string);
    void StopBGM();

    // SE: Sound Effect for short
    void PlaySE(std::string);

};

#endif 
