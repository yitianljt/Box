//
//  SpriteRunner.h
//  ShareTest
//
//  Created by jintao on 14-5-28.
//
//

#ifndef __ShareTest__SpriteRunner__
#define __ShareTest__SpriteRunner__

#include <iostream>

#include "cocos2d.h"

typedef enum {
    kRunerWalk,
    kRunerJump
    
}RunerState;

class SpriteRunner:public cocos2d::CCSprite
{
public:
    SpriteRunner();
    ~SpriteRunner();
    
    virtual bool init();
    //virtual void initActions();
    //virtual void setColor(const cocos2d::Color3B& color3);
    

    
    //PlayerState getState() { return this->m_ePlayerState; }
    //void setState(PlayerState playerState) { this->m_ePlayerState = playerState; }
    
    //int getEggs() { return this->m_iEggs; }
    //void onAcceleration(cocos2d::Acceleration* acc);
    
    //void stand();
    //void walk();
    void jump();
    //void shooted();
    void injured();
    void dead();
    void callbackJump();
    
    CREATE_FUNC(SpriteRunner);
    CC_SYNTHESIZE(float, m_fVelocity, Velocity);
    
protected:
    //PlayerState m_ePlayerState;
    //int m_iEggs;
    //bool m_bAccRight;
    RunerState _runnerState;
    cocos2d::Point _ptJump;

    
};




#endif /* defined(__ShareTest__SpriteRunner__) */
