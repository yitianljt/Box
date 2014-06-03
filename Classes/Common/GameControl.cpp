//
//  GameControl.cpp
//  ShareTest
//
//  Created by jintao on 14-5-18.
//
//

#include "GameControl.h"
#include "SceneLaunch.h"
#include "SceneGame.h"

USING_NS_CC;
BaseComScene* GameControl::scene(SceneTag tag)
{
    BaseComScene* scene = NULL;
    
    switch (tag) {
        case kSceneLaunch:
        scene = SceneLaunch::create();
        break;
        case kSceneGame:
        scene = SceneGame::create();
        break;
        default:
        break;
    }
    
    return  scene;
}
