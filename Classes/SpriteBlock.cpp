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
{}


SpriteBlock::~SpriteBlock()
{
    
}
bool SpriteBlock::init()
{
    if (initWithFile("player@2x.png")) {
        //this->setContentSize(CCSize(getContentSize().width-23,getContentSize().height-23));
        
        return true;
    }
    return false;
}

void SpriteBlock::move(float fd)
{
    fSpeed = fd;
    schedule(schedule_selector(SpriteBlock::update),0.01f);
}

void SpriteBlock::update(float ft)
{
    this->setPosition(this->getPosition() + CCPoint(fSpeed,0));
}
