//
//  SpriteBlock.cpp
//  ShareTest
//
//  Created by jintao on 14-5-29.
//
//

#include "SpriteBlock.h"
USING_NS_CC;


SpriteBlock::SpriteBlock()
{
    setisNeedCount(false);
}


SpriteBlock::~SpriteBlock()
{
    
}
bool SpriteBlock::init()
{
   // if (initWithFile("player@2x.png",Rect(4,4,60,60))) {
     if (initWithFile("square.png")) {
         this->setColor(Color3B(140,153,151 ));
        //this->setContentSize(Size(getContentSize().width-2,getContentSize().height-2));
         auto body = PhysicsBody::createBox(Size(60,60));
         this->setPhysicsBody(body);
        return true;
    }
    return false;
}

void SpriteBlock::move(float fd  )
{
    schedule(schedule_selector(SpriteBlock::update),0.01f);
    _fSpeed = fd;

}

void SpriteBlock::update(float ft)
{
    this->setPosition(this->getPosition() + Point(_fSpeed,0));
}




