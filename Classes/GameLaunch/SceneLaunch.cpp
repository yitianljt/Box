//
//  SceneLaunch.cpp
//  ShareTest
//
//  Created by jintao on 14-5-18.
//
//

#include "SceneLaunch.h"
#include "LayerLaunch.h"
USING_NS_CC;

SceneLaunch::SceneLaunch()
{

}

SceneLaunch::~SceneLaunch()
{
    
}

bool SceneLaunch::init()
{
    if (BaseComScene::init()) {
        //launch场景
        LayerLaunch* layerBg = LayerLaunch::create();
        addChild(layerBg,0);
        
        return true;
    }
    return false;
}

void SceneLaunch::onEnter()
{
    BaseComScene::onEnter();
}