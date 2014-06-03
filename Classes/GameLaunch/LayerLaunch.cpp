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
    Size sizeWin = Director::getInstance()->getWinSize();
    if (!Layer::init()) {
        return false;
    }
    

    LayerColor* layerBg = CCLayerColor::create(Color4B(255, 255, 0, 0), sizeWin.width, sizeWin.height);

    addChild(layerBg,0);
    Sprite* spNormal = Sprite::create();
    //MenuItemLabel* btnItem = CCMenuItemLabel::create(CCLabelTTF::create("开始游戏", "黑体", 40), this, menu_selector(LayerLaunch::callbackStart));
    MenuItemLabel* btnItem = MenuItemLabel::create(LabelTTF::create("开始游戏", "黑体", 40), [](Object* sender){
    Director::getInstance()->replaceScene(GameControl::scene(kSceneGame));
});
    
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
    Layer::onEnter();
}
void LayerLaunch::onExit()
{
    Layer::onExit();
}

void LayerLaunch::callbackStart(CCObject* obj)
{
    CCLog("callbackStart");
    CCDirector::sharedDirector()->replaceScene(GameControl::scene(kSceneGame));
}




