//
//  SceneGame.cpp
//  ShareTest
//
//  Created by jintao on 14-5-18.
//
//

#include "SceneGame.h"
#include "LayerGame.h"
USING_NS_CC;

SceneGame::SceneGame()
{
    
}

SceneGame::~SceneGame()
{
    
}

bool SceneGame::init()
{
    if (BaseComScene::init()) {
        //launch场景
        
        LayerGame* layerBg = LayerGame::create();
        this->addChild(layerBg,0);
        
        
//        GuideLayer* layerGuide = GuideLayer::create();
//        this->addChild(layerGuide);
        return true;
    }
    return false;
}

void SceneGame::onEnter()
{
    BaseComScene::onEnter();
}