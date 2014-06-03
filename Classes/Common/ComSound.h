//
//  ComSound.h
//  CrazyBox
//
//  Created by jintao on 14-6-3.
//
//

#ifndef __CrazyBox__ComSound__
#define __CrazyBox__ComSound__

#include <iostream>

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Common.h"
#include <stack>

enum {
    kBSSound_FxOnly,                    //!Other apps will be able to play audio
    kBSSound_FxPlusMusic,                //!Only this app will play audio
    kBSSound_FxPlusMusicIfNoOtherAudio,    //!If another app is playing audio at start up then allow it to continue and don't play music
    kBSSound_MediaPlayback,                //!This app takes over audio e.g music player app
    kBSSound_PlayAndRecord                //!App takes over audio and has input and output
};


#define SOUND_ID_MUTE 0xFEEDBAB // same as CD_MUTE defined in CocosDension.h

typedef int MUSIC_PRIORITY;

typedef struct MusicHandler {
    const char* music;
    MUSIC_PRIORITY priority;
    MusicHandler(const char* pMusic, MUSIC_PRIORITY pPriority) : music(pMusic), priority(pPriority)
    {};
} MusicHandler;

class ComSound : public cocos2d::Ref {
    SINGLETON(ComSound);
public:
    void setIsMute(bool pIsMute);
    bool getIsMute() {return _isMute;};
    void setIsMusicMute(bool pIsMute);
    void setIsEffectMute(bool pIsMute);
    bool getIsMusicMute() {return _isMusicMute;};
    bool getIsEffectMute() {return _isEffectMute;};
    void switchMusicMute(){setIsMusicMute(!getIsMusicMute());};
    void switchEffectMute(){setIsEffectMute(!getIsEffectMute());};
    void setMusicVolume(float pVolume);
    void setEffectVolume(float pVolume);
    float getMusicVolume();
    float getEffectVolume();
    
    bool pushMusic(const char* pMusic, MUSIC_PRIORITY pPriority); //always loop
    void popMusic();
    void playMusic(const char* pMusic);
    void stopMusic();
    
    void preloadEffects(const char* pEffect, ...);
    unsigned int playEffect(const char* pEffect, bool pIsLoop = false);
    void stopEffect(unsigned int nSoundId);
    void stopAllEffects();
    void configure(int pMode);
    void dump();
    void active();
    
private:
    void _playMusic(const char* pMusic);
    
private:
    bool _isMute;
    bool _isMusicMute;
    bool _isEffectMute;
    float _musicVolume;
    float _effectVolume;
    MusicHandler* _currentMusicHandler;
    std::stack<MusicHandler*> *_stack;
    
};

#endif /* defined(__CrazyBox__ComSound__) */
