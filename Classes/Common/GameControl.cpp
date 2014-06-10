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
#include "LayerGame.h"

USING_NS_CC;
Scene* GameControl::scene(SceneTag tag)
{
    BaseComScene* scene = NULL;
    
    switch (tag) {
        case kSceneLaunch:
        scene = SceneLaunch::create();
        break;
        case kSceneGame:
        {
            scene = SceneGame::createWithPhysics();
            scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
            LayerGame* layerBg = LayerGame::create();
            scene->addChild(layerBg,0);
        }
        break;
        case kSceneResult:
              //scene = SceneResult::create();
        default:
        break;
    }
    
    return  scene;
}
