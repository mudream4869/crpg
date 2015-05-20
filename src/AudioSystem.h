#ifndef AUDIO_DEF
#define AUDIO_DEF

#include <string>

namespace AudioSystem{
    
    /**
     *  @brief Init the Audio envirnment, should be called at beginning
     */
    void InitAudioSystem();

    /**
     *  @brief Should be called at AtExit
     */
    void ExitAudioSystem();
    
    /**
     *  @brief Starting bgm 
     *  @param 
     *      bgm_name : the filename of bgm. 
     *                 Should under sound/bgm/ and should be ogg or wav
     */
    void PlayBGM(std::string bgm_name);
    
    /**
     *  @brief Stop Certain bgm
     */
    void StopBGM();
    
    /**
     *  @brief Play sound effect
     *  @param 
     *      se_name : the filename sound effect.
     *                Should under sound/se/ and should be ogg or wav
     */
    void PlaySE(std::string se_name);
};

#endif 
