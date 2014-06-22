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

#define PTM_RATIO 32

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
    LayerGradient* layer1 = LayerGradient::create(Color4B(110,210,200,255), Color4B(110,210,190,255), Point(.0f, .0f));
    addChild(layer1, kBgLayerOrder);
    
    _spRuner = SpriteRunner::create();
    _spRuner->setPosition(Point(200,290));
    //_spRuner->addBoxBodyForSprite(_spRuner);
    auto body = PhysicsBody::createBox(Size(60,60));
    _spRuner->setPhysicsBody(body);
    //body->setRotationEnable(true);
    addChild(_spRuner);
    //CCDirector::getInstance()->getEventDispatcherer()->addTargetedDelegate(this, 0, true);
    this->m_pSpriteBatchNode = CCSpriteBatchNode::create("square.png", 100);
    addChild(m_pSpriteBatchNode,kCloudOrder);
    

    
    
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(LayerGame::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(LayerGame::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(LayerGame::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    //云朵背景
    _parallax = ParallaxNode::create();
    this->addChild(_parallax,kCloudOrder);
    
    _cloudBackLayer = CloudLayer::create(BSWinSize().width, kCloudBack);
    _parallax->addChild(_cloudBackLayer, 1, Vec2(0.5,0), Vec2(0,0) );

    _cloudFrontLayer = CloudLayer::create(BSWinSize().width, kCloudFront);
    _parallax->addChild(_cloudFrontLayer, 2, Vec2(0.7,0), Vec2(0,0) );
    
    
    
    _parallax2 = ParallaxNode::create();
    Point pt = _parallax2->getAnchorPoint();
    this->addChild(_parallax2,1);
    CloudLayer *cloudBackLayer_ = CloudLayer::create(BSWinSize().width, kCloudBack);
    _parallax2->addChild(cloudBackLayer_, 1, Vec2(0.5,0), Vec2(0,0) );
    CloudLayer* cloudFrontLayer_ = CloudLayer::create(BSWinSize().width, kCloudFront);
    _parallax2->addChild(cloudFrontLayer_, 2, Vec2(0.7,0), Vec2(0,0) );
    _parallax2->setPositionX(_cloudFrontLayer->getcloudLayerWidth());
    
    //ground
    _spGround1 = Sprite::create("ground.png");
    _spGround1->setAnchorPoint(Point(0,0));
    _spGround1->setPosition(Point(0,0));
    this->addChild(_spGround1,kGroundOrder);
    _spGround2 = Sprite::create("ground.png");
    _spGround2->setAnchorPoint(Point(0,0));
    _spGround2->setPosition(_spGround1->getPosition()+Point(_spGround1->getContentSize().width,0));
    this->addChild(_spGround2,kGroundOrder);
    
    CCLOG("%f,%f (2) %f,%f",_spGround1->getPositionX(),_spGround1->getPositionY(),_spGround2->getPositionX(),_spGround2->getPositionY());

    //一进入来移动
    this->schedule(schedule_selector(LayerGame::updateGround), 0.01f);

    
    
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
    _parallax->setPositionX(_parallax->getPositionX()-3);
    _parallax2->setPositionX(_parallax2->getPositionX()-3);
    
    if (_parallax->getPositionX()<-(_cloudBackLayer->getcloudLayerWidth()*2))
    {
        _parallax->setPositionX(_parallax2->getPositionX()+_cloudBackLayer->getcloudLayerWidth()*2);
    }
    
    if (_parallax2->getPositionX()<-(_cloudBackLayer->getcloudLayerWidth()*2))
    {
        _parallax2->setPositionX(_parallax->getPositionX()+_cloudBackLayer->getcloudLayerWidth()*2);
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
    int itype = (5*CCRANDOM_0_1());;
    CCLOG("iType = %d",itype);
    setCurStartPos(getDefaultPos());
    addBlockType(itype);
}


bool LayerGame::isCollison(Sprite* spRuner,Sprite* spBlock)
{
    if (spRuner->boundingBox().intersectsRect(spBlock->boundingBox()) )
    {
        return  true;
    }
    return false;
}


void LayerGame::gameover()
{
    this->unschedule(schedule_selector(LayerGame::update));
    this->unschedule(schedule_selector(LayerGame::addBlock));
    
    //Director::getInstance()->pushScene(GameControl::scene(SceneTag::kSceneResult));


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
    return Point(BSWinSize().width,288);
}

void LayerGame::updateGround(float fDelta)
{

    
    std::vector<Sprite*>  blockNodes = m_pSpriteBatchNode->getDescendants();
    for (auto child:blockNodes )
    {
        
        SpriteBlock* spBlock = dynamic_cast<SpriteBlock*>(child);
        /*
        if (spBlock && isCollison(spBlock, _spRuner)) {
            _spRuner->dead();
        }*/
        //spBlock->setPositionX(spBlock->getPositionX()-8.0);

    }

    _spGround1->setPosition(_spGround1->getPosition()+ Point(-8,0));
    _spGround2->setPosition(_spGround2->getPosition()+ Point(-8,0));
    
    if (_spGround1->getPositionX()< -BSWinSize().width) {
        _spGround1->setPositionX(_spGround2->getPositionX()+_spGround2->getContentSize().width);
    }
    else if (_spGround2->getPositionX()< -BSWinSize().width)
    {
        _spGround2->setPositionX(_spGround1->getPositionX()+_spGround1->getContentSize().width);
    }


}

void LayerGame::addBlockType(int iType)
{
    iType = 0;
    switch (iType) {
        case 0:
        {
            SpriteBlock* spBlock = SpriteBlock::create();
            m_pSpriteBatchNode->addChild(spBlock);
            spBlock->setPosition(getCurStartPos());
            spBlock->setisNeedCount(true);
            
            auto body = PhysicsBody::createBox(Size(60,60));
            spBlock->setPhysicsBody(body);
            
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
            
            //spBlock->move();
            //spBlock2->move();


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
//            spBlock->move();
//            spBlock2->move();
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
            
//            spBlock->move();
//            spBlock2->move();
//            spBlock3->move();
            
            break;
        }
            
        case 4:
        {
            //0
            //00
            SpriteBlock* spBlock = SpriteBlock::create();
            m_pSpriteBatchNode->addChild(spBlock);
            spBlock->setPosition(getCurStartPos());
            
            SpriteBlock* spBlock2 = SpriteBlock::create();
            m_pSpriteBatchNode->addChild(spBlock2);
            spBlock2->setPosition(getCurStartPos()+Point(0,spBlock->getContentSize().height));
            
            
            SpriteBlock* spBlock3 = SpriteBlock::create();
            m_pSpriteBatchNode->addChild(spBlock3);
            spBlock3->setPosition(getCurStartPos()+Point(spBlock->getContentSize().width,0));
            spBlock3->setisNeedCount(true);
            
//            spBlock->move();
//            spBlock2->move();
//            spBlock3->move();
            
            break;

        }
            
        case 5:
        {
            //   *
            //  **
            SpriteBlock* spBlock = SpriteBlock::create();
            m_pSpriteBatchNode->addChild(spBlock);
            spBlock->setPosition(getCurStartPos());
            
            SpriteBlock* spBlock2 = SpriteBlock::create();
            m_pSpriteBatchNode->addChild(spBlock2);
            spBlock2->setPosition(getCurStartPos()+Point(spBlock->getContentSize().width,0));
            
            
            SpriteBlock* spBlock3 = SpriteBlock::create();
            m_pSpriteBatchNode->addChild(spBlock3);
            spBlock3->setPosition(getCurStartPos()+Point(spBlock->getContentSize().width,spBlock->getContentSize().width));
            spBlock3->setisNeedCount(true);
            
//            spBlock->move();
//            spBlock2->move();
//            spBlock3->move();
            
            break;
        
        }
        case 6:
        {
            //***
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
            
//            spBlock->move();
//            spBlock2->move();
//            spBlock3->move();
            
            break;

            
        }

        
            
        default:
            break;
    }
}

void LayerGame::initPhysics()
{
//    //step :1
//    b2Vec2 gravity;// step: 1
//    gravity.Set(0.0f, 0.0); // direction of the sprite runs,base on the GL position,
//
//
//    //step :2
//    _world  = new b2World(gravity);
//    _world->SetAllowSleeping(true); // pause all ,init the box2d world
//    _world->SetContinuousPhysics(true); // resume the box2d
//
//
//    //
//    
//    //step: 3, defint the body
//    b2BodyDef groundbodyDef;
//    groundbodyDef.position.Set(0, 0);
//    b2Body *body = _world->CreateBody(&groundbodyDef);
//    
//    
//    //
//    b2BodyDef bodyDef;
//    bodyDef.type = b2_dynamicBody;
//    bodyDef.position.Set(_spRuner->getPositionX()/PTM_RATIO, _spRuner->getPositionY()/PTM_RATIO);
//    bodyDef.userData = _spRuner;
//    
//    //
//    b2Body* bodyRuner = _world->CreateBody(&bodyDef);
//    
//    b2PolygonShape dynamicBox;
//    dynamicBox.SetAsBox(_spRuner->getContentSize().width/PTM_RATIO/2, _spRuner->getContentSize().height/PTM_RATIO/2);
//    
//    b2FixtureDef fixtureDef;
//    fixtureDef.shape = &dynamicBox;
//    fixtureDef.density = 1.0f;
//    fixtureDef.friction = 0.0f;
//    
//    bodyRuner->CreateFixture(&fixtureDef);
//    
//    
//    int velocity= 8;
//    int position =1;
//    _world->Step(0.01,velocity,position);
//
//    
    
    
    
    
}
