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
#include "CloudLayer.h"
#include "Common.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Box2D/Box2D.h"
#include "SpriteRunner.h"

typedef enum {
    kLevel1=1,
    kLevle2,
    kLevle3,
    kLevle4

}GameLevel;

typedef enum {
    kWaitStart,
    kPlaying,
    kGameOver
    
}kGameStatus;

typedef enum {
    kBgLayerOrder,
    kGroundOrder,
    kCloudOrder,
    
}kZOrder;


class LayerGame:public cocos2d::Layer
{
public:
    LayerGame();
    ~LayerGame();
    COM_CREATE_FUNC(LayerGame);
    
    
    
    virtual void onEnter();
    virtual void onExit();
    
    //void retry();

    void start(cocos2d::Ref* pSender = nullptr);
    void stop();
    void addBlock(float fDelta);
    void addBlockType();
    void addBlockType(int iType);
    void getCurLevel();
    cocos2d::Point  getDefaultPos();
    CC_SYNTHESIZE(cocos2d::Point, _curStartPos, CurStartPos);
    void update(float fDelta);
    void updateGround(float fDelta);

    void initPhysics();

    virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

    
    
    void callbackStart(cocos2d::Ref* obj,cocos2d::extension::Control::EventType type);
    bool isCollison(cocos2d::Sprite* sp1,cocos2d::Sprite* sp2);
    
    void gameover();
    void setPhyWorld(cocos2d::PhysicsWorld* world){ _world = world;};
    bool onContactBegin(cocos2d::PhysicsContact& contact);

    
private:
    int  _gameStatus;
    void playBgMusic();
    void stopBgMusic();
    SpriteRunner* _spRuner;
    cocos2d::SpriteBatchNode* m_pSpriteBatchNode;
    cocos2d::ParallaxNode* _parallax;
    cocos2d::ParallaxNode* _parallax2;
    
    cocos2d::LayerColor* layerGround1;
    cocos2d::LayerColor* layerGround2;
    
    cocos2d::Sprite* _spGround1;
    cocos2d::Sprite* _spGround2;
    

    CloudLayer* _cloudBackLayer;
    CloudLayer* _cloudFrontLayer;
    

    GameLevel _gameLevel;
    cocos2d::PhysicsWorld* _world;
    
    
    
};


#endif /* defined(__ShareTest__LayerGame__) */
