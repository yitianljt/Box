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
    if (initWithFile("player@2x.png")) {
        this->setContentSize(Size(getContentSize().width-2,getContentSize().height-2));
        
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




