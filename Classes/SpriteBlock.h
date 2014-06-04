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

class SpriteBlock : public cocos2d::Sprite
{
public:
    SpriteBlock();
    ~SpriteBlock();
    virtual bool init();
    
    CREATE_FUNC(SpriteBlock);
    void move(float fd = -7.0);
    void update(float ft);
    CC_SYNTHESIZE(bool, _isNeedCount, isNeedCount);
    
private:
    float _fSpeed;
    int   _iScore;
    
};
#endif /* defined(__ShareTest__SpriteBlock__) */
