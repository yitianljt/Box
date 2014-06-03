//
//  LayerLaunch.cpp
//  ShareTest
//
//  Created by jintao on 14-5-18.
//
//

#include "LayerLaunch.h"
#include "GameControl.h"


USING_NS_CC;


COM_CREATE_FUNC_IMPL(LayerLaunch);


LayerLaunch::LayerLaunch()
{}
LayerLaunch::~LayerLaunch(){}

bool LayerLaunch::init()
{
    CCSize sizeWin = CCDirector::sharedDirector()->getWinSize();
    if (!CCLayer::init()) {
        return false;
    }
    

    CCLayerColor* layerBg = CCLayerColor::create(ccc4(255, 255, 0, 0), sizeWin.width, sizeWin.height);

    addChild(layerBg,0);
    CCSprite* spNormal = CCSprite::create();
    CCMenuItemLabel* btnItem = CCMenuItemLabel::create(CCLabelTTF::create("开始游戏", "黑体", 40), this
                                                       , menu_selector(LayerLaunch::callbackStart));
    CCMenuItemSprite* btnStart = CCMenuItemSprite::create(spNormal,spNormal,this,menu_selector(LayerLaunch::callbackStart));
    
    //btnStart->setPosition(ccp(sizeWin.width/2,sizeWin.height/2));
    
    CCMenu* menu = CCMenu::create(btnItem,NULL);
    menu->setPosition(ccp(sizeWin.width/2,sizeWin.height/2));
    layerBg->addChild(menu, 1);
    
    //layerBg->addChild(btnStart);
    
    
    return true;
    
    
}

void LayerLaunch::onEnter()
{
    CCLayer::onEnter();
}
void LayerLaunch::onExit()
{}

void LayerLaunch::callbackStart(CCObject* obj)
{
    CCLog("callbackStart");
    CCDirector::sharedDirector()->replaceScene(GameControl::scene(kSceneGame));
}




