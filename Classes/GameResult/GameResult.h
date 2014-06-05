//
//  GameResult.h
//  CrazyBox
//
//  Created by jintao on 14-6-5.
//
//

#ifndef __CrazyBox__GameResult__
#define __CrazyBox__GameResult__

#include <iostream>
#include "BaseComScene.h"
#include "cocos2d.h"


class GameResult:public BaseComScene
{
public:
    GameResult();
    ~GameResult();
    
    virtual bool init();
    virtual void onEnter();
    
    
    CREATE_FUNC(GameResult);
    
    
    
};


#endif /* defined(__CrazyBox__GameResult__) */
