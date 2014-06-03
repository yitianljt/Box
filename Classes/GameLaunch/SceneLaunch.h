//
//  SceneLaunch.h
//  ShareTest
//
//  Created by jintao on 14-5-18.
//
//

#ifndef __ShareTest__SceneLaunch__
#define __ShareTest__SceneLaunch__

#include <iostream>
#include "BaseComScene.h"
#include "cocos2d.h"


class SceneLaunch:public BaseComScene
{
public:
    SceneLaunch();
    ~SceneLaunch();
    
    virtual bool init();
    virtual void onEnter();

    
    CREATE_FUNC(SceneLaunch);
    

    
};


#endif /* defined(__ShareTest__SceneLaunch__) */
