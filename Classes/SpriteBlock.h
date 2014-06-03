//
//  SpriteBlock.h
//  ShareTest
//
//  Created by jintao on 14-5-29.
//
//

#ifndef __ShareTest__SpriteBlock__
#define __ShareTest__SpriteBlock__

#include <iostream>
#include "cocos2d.h"

class SpriteBlock : public cocos2d::CCSprite
{
public:
    SpriteBlock();
    ~SpriteBlock();
    virtual bool init();
    
    CREATE_FUNC(SpriteBlock);
    void move(float fd);
    void update(float ft);

    
    
private:
    void move();
    float fSpeed;
    
};
#endif /* defined(__ShareTest__SpriteBlock__) */
