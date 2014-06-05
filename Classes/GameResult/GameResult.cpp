//
//  GameResult.cpp
//  CrazyBox
//
//  Created by jintao on 14-6-5.
//
//

#include "GameResult.h"
#include "LayerGame.h"
USING_NS_CC;

GameResult::GameResult()
{
    
}

GameResult::~GameResult()
{
    
}

bool GameResult::init()
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

void GameResult::onEnter()
{
    BaseComScene::onEnter();
}