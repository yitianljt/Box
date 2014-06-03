//
//  SceneGame.h
//  ShareTest
//
//  Created by jintao on 14-5-18.
//
//

#ifndef __ShareTest__SceneGame__
#define __ShareTest__SceneGame__

#include <iostream>
#include <iostream>
#include "BaseComScene.h"
#include "cocos2d.h"


class SceneGame:public BaseComScene
{
    public:
    SceneGame();
    ~SceneGame();
    
    virtual bool init();
    virtual void onEnter();
    
    
    CREATE_FUNC(SceneGame);
    
    
    
};


#endif /* defined(__ShareTest__SceneGame__) */
