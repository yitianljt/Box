//
//  GameControl.h
//  ShareTest
//
//  Created by jintao on 14-5-18.
//
//

#ifndef __ShareTest__GameControl__
#define __ShareTest__GameControl__

#include <iostream>
#include "BaseComScene.h"
typedef enum {
    kSceneLaunch,
    kSceneGame,
    kSceneResult,
    
}SceneTag;

class GameControl{
public:
    static BaseComScene* scene(SceneTag tag);
};

#endif /* defined(__ShareTest__GameControl__) */
