//
//  SpriteRunner.cpp
//  ShareTest
//
//  Created by jintao on 14-5-28.
//
//

#include "SpriteRunner.h"
#include "CommonTool.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
USING_NS_CC;

SpriteRunner::SpriteRunner()
{
    m_fVelocity = 0.0f;
    _ptJump = Point(0, 0);
    _runnerState = kRunerWalk;
}
SpriteRunner::~SpriteRunner()
{}

bool SpriteRunner::init() {
    if (initWithFile("player@2x.png")) {
        //this->setContentSize(Size(this->getContentSize().width-4,this->getContentSize().height-4));
        Size originSize = this->getContentSize();
        //this->setContentSize(Size(10,10));
        //setAnchorPoint((Point(originSize.width/10.0,(originSize.height-10)/10.0)));

        return true;
    }
    
    return false;
}
/*
void SpriteRunner::findTarget(cocos2d::CCPoint &pos) {
    this->setPosition(pos, CCDirector::getInstance()->getVisibleSize());
}

void SpriteRunner::move() {
    this->stopAllActions();
    this->runAction(Sequence::create(MoveTo::create(m_fDuration, Point(this->getPositionX(), this->m_fCenterToBottom+VisibleRect::leftBottom().y)), CallFunc::create(CC_CALLBACK_0(SpriteArrow::fadeOut, this)), NULL));
}

void SpriteRunner::move(float duration) {
    this->m_fDuration = duration;
    this->move();
}

void SpriteRunner::fadeOut() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("end.mp3");
    this->m_bValid = false;
    this->runAction(Sequence::create(FadeOut::create(0.3f), CallFunc::create(CC_CALLBACK_0(SpriteArrow::onFadeOut, this)), NULL));
}

void SpriteRunner::onFadeOut() {
    SceneMain* sceneMain = dynamic_cast<SceneMain*>(getScene());
    
    if(sceneMain) {
        sceneMain->updateArrowsNumShow();
    }
    this->removeFromParent();
}*/

void SpriteRunner::dead()
{
    //ParticleSystem* m_emitter1 = ParticleSystemQuad::create("testoc.plist");
    //addChild(m_emitter1);
    //this->getParent()->addChild(m_emitter1);
    CCLOG("dead");
}

void SpriteRunner::callbackJump()
{
    this->_runnerState = kRunerWalk;
}



void SpriteRunner::jump()
{
    if (_runnerState == kRunerWalk) {
        _ptJump = this->getPosition();
    }
    else if (_runnerState == kRunerJump)
    {
       // this->setRotation(0.0f);
        return;
    }
    this->stopAllActions();

    _runnerState = kRunerJump;
    ActionInterval* jumpto = CCJumpTo ::create(1, _ptJump, this->getContentSize().height*3+60, 1 );
    ActionInterval * rotateBy1 = RotateBy::create(0.5, 180);
    ActionInterval * rotateBy2 = RotateBy::create(0.5, 180);

    auto call = [this](){CCLOG("test");};
    
    
    FiniteTimeAction * spawn =CCSpawn::create(jumpto ,Sequence::create(rotateBy1,rotateBy2,NULL),NULL);
    this->runAction(Sequence::create(spawn,CallFunc::create([&](){this->_runnerState = kRunerWalk;}), CallFunc::create([&](){
        //回调动作代码
        CCLOG("test3");
    }), NULL));

    
}