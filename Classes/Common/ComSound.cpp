//
//  ComSound.cpp
//  CrazyBox
//
//  Created by jintao on 14-6-3.
//
//

#include "ComSound.h"
#include <stack>

using namespace std;


SINGLETON_IMPL(ComSound)

bool ComSound::init() {
    _stack = new stack<MusicHandler*>();
    _currentMusicHandler = NULL;
    _musicVolume = 1.0f;
    _effectVolume = 1.0f;
    setIsMusicMute(false);
    setIsEffectMute(false);
    return true;
}

void ComSound::setIsMute(bool pIsMute) {
    _isMute = pIsMute;
    setIsMusicMute(_isMute);
    setIsEffectMute(_isMute);
}

void ComSound::setIsMusicMute(bool pIsMute) {
    _isMusicMute = pIsMute;
    if (_isMusicMute) {
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);
    } else {
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(_musicVolume);
    }
}

void ComSound::setIsEffectMute(bool pIsMute) {
    _isEffectMute = pIsMute;
    if (_isEffectMute) {
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0);
    } else {
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(_effectVolume);
    }
}

bool ComSound::pushMusic(const char *pMusic, MUSIC_PRIORITY pPriority) {
    if (!_currentMusicHandler || pPriority <= _currentMusicHandler->priority) {
        MusicHandler* handler = new MusicHandler(pMusic, pPriority);
        _stack->push(handler);
        _playMusic(pMusic);
        return true;
    }
    return false;
}

void ComSound::popMusic() {
    if (_stack->empty()) {
        return;
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    delete _stack->top();
    _stack->pop();
    if (!_stack->empty()) {
        _playMusic(_stack->top()->music);
    }
}

void ComSound::playMusic(const char *pMusic) {
    stopMusic();
    _playMusic(pMusic);
}

void ComSound::stopMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void ComSound::preloadEffects(const char *pEffect, ...) {
    va_list params;
    va_start(params, pEffect);
    const char *pFirst = pEffect;
    while(pFirst) {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(pFirst);
        pFirst = va_arg(params, const char*);
    }
    va_end(params);
}

unsigned int ComSound::playEffect(const char *pEffect, bool pIsLoop) {
    return CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(pEffect, pIsLoop);
}

void ComSound::stopEffect(unsigned int nSoundId) {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(nSoundId);
}

void ComSound::stopAllEffects() {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}

void ComSound::_playMusic(const char *pMusic) {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(pMusic, true);
}

void ComSound::setMusicVolume(float pVolume) {
    _musicVolume = pVolume;
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(pVolume);
}

void ComSound::setEffectVolume(float pVolume) {
    _effectVolume = pVolume;
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(pVolume);
    
}

float ComSound::getEffectVolume() {
    return _effectVolume;
}

float ComSound::getMusicVolume() {
    return _musicVolume;
}