//
//  LayerGame.h
//  ShareTest
//
//  Created by jintao on 14-5-18.
//
//

#ifndef __ShareTest__LayerGame__
#define __ShareTest__LayerGame__

#include <iostream>
#include "Common.h"
#include "cocos2d.h"
#include "SpriteRunner.h"

typedef enum {
    kLevel1=1,
    kLevle2,
    kLevle3,
    kLevle4

}GameLevel;


class LayerGame:public cocos2d::Layer
{
public:
    LayerGame();
    ~LayerGame();
    COM_CREATE_FUNC(LayerGame);
    
    
    
    virtual void onEnter();
    virtual void onExit();
    
    //void retry();

    void start();
    void stop();
    void addBlock(float fDelta);
    void addBlockType();
    void addBlockType(int iType);
    void getCurLevel();
    cocos2d::Point  getDefaultPos();
    CC_SYNTHESIZE(cocos2d::Point, _curStartPos, CurStartPos);
    void update(float fDelta);

    virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

    
    
    void callbackStart(cocos2d::Ref* obj);
    bool isCollison(cocos2d::Sprite* sp1,cocos2d::Sprite* sp2);
    
    void gameover();
    
private:
    
    void playBgMusic();
    void stopBgMusic();
    SpriteRunner* _spRuner;
    cocos2d::SpriteBatchNode* m_pSpriteBatchNode;
    
    GameLevel _gameLevel;
    
    
};


#endif /* defined(__ShareTest__LayerGame__) */
