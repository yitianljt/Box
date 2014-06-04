//
//  LayerGame.cpp
//  ShareTest
//
//  Created by jintao on 14-5-18.
//
//

#include "BaseComScene.h"
#include "Common.h"
#include "CommonTool.h"
#include "CommonTool.h"
#include "ComSound.h"
#include "GameControl.h"
#include "LayerGame.h"
#include "SpriteRunner.h"
#include "SpriteBlock.h"
#include <vector>


USING_NS_CC;



COM_CREATE_FUNC_IMPL(LayerGame);


LayerGame::LayerGame()
{
    m_pSpriteBatchNode = NULL;
    _gameLevel = kLevel1;
}
LayerGame::~LayerGame(){}

bool LayerGame::init()
{
    Size sizeWin = CCDirector::getInstance()->getWinSize();
    if (!CCLayer::init()) {
        return false;
    }
    //背景
    LayerGradient* layer1 = LayerGradient::create(Color4B(60,110,110,255), Color4B(110,210,190,255), Point(.0f, .0f));
    addChild(layer1, 0);
    
//    GroundLayer* layerGround = GroundLayer::create();
//    addChild(layerGround);
    
    _spRuner = SpriteRunner::create();
    
    _spRuner->setPosition(Point(200,400));
    //_spRuner->setRotation(45);
    addChild(_spRuner);
    
    //CCDirector::getInstance()->getEventDispatcherer()->addTargetedDelegate(this, 0, true);
    
    //this->m_pSpriteBatchNode=CCSpriteBatchNode::create("main.png", 100);

    this->m_pSpriteBatchNode = CCSpriteBatchNode::create("player@2x.png", 100);
    addChild(m_pSpriteBatchNode);
    start();
    
    glLineWidth( 5.0f );
    cocos2d::DrawPrimitives::setDrawColor4F(255,0,0,40);
    DrawPrimitives::drawLine(Point(0, 0), Point(200, 400));
    /*
    
    CCLayerColor* layerBg = CCLayerColor::create(ccc4(0, 255, 255, 255), sizeWin.width, sizeWin.height);
    addChild(layerBg,0);
    CCSprite* spNormal = CCSprite::create();
    CCMenuItemSprite* btnStart = CCMenuItemSprite::create(spNormal,spNormal,this,menu_selector(LayerGame::callbackStart));
    btnStart->setPosition(ccp(sizeWin.width/2,sizeWin.height/2));
    
    CCMenuItemLabel* menuItem = CCMenuItemLabel::create(CCLabelTTF::create("播放视频", "黑体", 40), this, menu_selector(LayerGame::callbackStart));
    
    CCMenu* menu = CCMenu::create(menuItem,NULL);
    
    menu->setPosition(ccp(sizeWin.width/2, sizeWin.height/2));
    this->addChild(menu);
    */
    
    
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(LayerGame::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(LayerGame::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(LayerGame::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    
    start();
    
    
    return true;
    
    
}

void LayerGame::onEnter()
{
    CCLayer::onEnter();
}
void LayerGame::onExit()
{
    CCLayer::onExit();
}

void LayerGame::callbackStart(Ref* obj)
{
    //PlayVideo::playVideo("opening_video.mp4",(CCLayer*)this);
}

void LayerGame::start()
{
    playBgMusic();
    this->schedule(schedule_selector(LayerGame::update), 0.01f);
    this->schedule(schedule_selector(LayerGame::addBlock), 3.0f );
}

void LayerGame::stop()
{
    this->unschedule(schedule_selector(LayerGame::update));
}


void LayerGame::update(float fDelta)
{
    
    std::vector<Sprite*>  blockNodes = m_pSpriteBatchNode->getDescendants();
    for (auto child:blockNodes )
    {
        SpriteBlock* spBlock = dynamic_cast<SpriteBlock*>(child);
        if (spBlock && isCollison(spBlock, _spRuner)) {
            CCLOG("xxxxx1=%f,x2=%f",_spRuner->getPositionX(),spBlock->getPositionX());
            CCLOG("w1=%f,w2=%f",_spRuner->getContentSize().width,spBlock->getContentSize().width);
            _spRuner->dead();


        }
    }
    
    
}

bool LayerGame::onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    return true;
}


void LayerGame::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    _spRuner->jump();
}

void LayerGame::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    
}


void LayerGame::addBlock(float fDelta)
{
    int itype = rand()%5;
    setCurStartPos(getDefaultPos());

    addBlockType(itype);
}


bool LayerGame::isCollison(Sprite* spRuner,Sprite* spBlock)
{
    if (spRuner->boundingBox().intersectsRect(spBlock->boundingBox()) )
    {
        _spRuner->dead();
        gameover();
    }
    
    
    
    return false;
}


void LayerGame::gameover()
{
    
}

void LayerGame::playBgMusic()
{
    ComSound::shared()->playMusic("music/Bg.m4a");
}

void LayerGame::stopBgMusic()
{
    ComSound::shared()->stopMusic();
}

void LayerGame::addBlockType()
{
    
    int itype = rand()%5;
    setCurStartPos(getDefaultPos());
    addBlockType(itype);
}

Point  LayerGame::getDefaultPos()
{
    return Point(BSWinSize().width,400);
}



void LayerGame::addBlockType(int iType)
{
    switch (iType) {
        case 0:
        {
            SpriteBlock* spBlock = SpriteBlock::create();
            m_pSpriteBatchNode->addChild(spBlock);
            spBlock->setPosition(getCurStartPos());
            spBlock->setisNeedCount(true);
            
            spBlock->move();

            
            break;

        }
        case 1:
        {
            SpriteBlock* spBlock = SpriteBlock::create();
            m_pSpriteBatchNode->addChild(spBlock);
            spBlock->setPosition(getCurStartPos());
            
            SpriteBlock* spBlock2 = SpriteBlock::create();
            m_pSpriteBatchNode->addChild(spBlock2);
            spBlock2->setPosition(getCurStartPos()+Point(spBlock->getContentSize().width,0));
            spBlock2->setisNeedCount(true);
            
            spBlock->move();
            spBlock2->move();


            break;
        }
        case 2:
        {
            SpriteBlock* spBlock = SpriteBlock::create();
            m_pSpriteBatchNode->addChild(spBlock);
            spBlock->setPosition(getCurStartPos());
            
            SpriteBlock* spBlock2 = SpriteBlock::create();
            m_pSpriteBatchNode->addChild(spBlock2);
            spBlock2->setPosition(getCurStartPos()+Point(0,spBlock->getContentSize().height));
            spBlock2->setisNeedCount(true);
            spBlock->move();
            spBlock2->move();
            break;
        }
            
        case 3:
        {
            SpriteBlock* spBlock = SpriteBlock::create();
            m_pSpriteBatchNode->addChild(spBlock);
            spBlock->setPosition(getCurStartPos());
            
            SpriteBlock* spBlock2 = SpriteBlock::create();
            m_pSpriteBatchNode->addChild(spBlock2);
            spBlock2->setPosition(getCurStartPos()+Point(spBlock->getContentSize().width,0));
            
            
            SpriteBlock* spBlock3 = SpriteBlock::create();
            m_pSpriteBatchNode->addChild(spBlock3);
            spBlock3->setPosition(getCurStartPos()+Point(spBlock->getContentSize().width*2,0));
            spBlock3->setisNeedCount(true);
            
            spBlock->move();
            spBlock2->move();
            spBlock3->move();
            
            break;
        }

        
            
        default:
            break;
    }

    
}
