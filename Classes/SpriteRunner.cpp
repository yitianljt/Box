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
    if (initWithFile("square.png")) {
        Size originSize = this->getContentSize();
        CCLOG("%f,%f",originSize.width,originSize.height);
        
        auto body = PhysicsBody::createBox(Size(60,60));
        body->setCategoryBitmask(1);    // 0001
        body->setCollisionBitmask(1);   // 0001
        body->setContactTestBitmask(1); // 0001
        this->setPhysicsBody(body);
        
        return true;
    }
    
    return false;
}

void SpriteRunner::dead()
{
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
        //return;
    }
    this->stopAllActions();
    _runnerState = kRunerJump;
    
    JumpTo* jumpto = JumpTo ::create(1, _ptJump, this->getContentSize().height*3+40, 1 );
    RotateBy * rotateBy1 = RotateBy::create(0.5, 180);
    RotateBy * rotateBy2 = RotateBy::create(0.5, 180);

    auto call = [this](){CCLOG("test");};
    FiniteTimeAction * spawn =Spawn::create(jumpto ,Sequence::create(rotateBy1,rotateBy2,NULL),NULL);
    this->runAction(Sequence::create(spawn,CallFunc::create([&](){this->_runnerState = kRunerWalk;}), CallFunc::create([&](){
        //回调动作代码
        CCLOG("test3");
    }), NULL));

    
}



