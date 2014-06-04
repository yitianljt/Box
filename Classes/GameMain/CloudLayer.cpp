//
//  CloudLayer.cpp
//  CrazyBox
//
//  Created by jintao on 14-6-4.
//
//

#include "CloudLayer.h"
#include "CommonTool.h"

USING_NS_CC;


CloudLayer::CloudLayer(float width,CloudDepth depth)
{
    _cloudDepth = depth;
}

CloudLayer::~CloudLayer()
{}

CloudLayer* CloudLayer::create(float width,CloudDepth depth)
{
    CloudLayer* node = new CloudLayer(width,depth);
    if (node && node->init(width)) {
        node->autorelease();
        return node;
    }
    else
    {
        CC_SAFE_DELETE(node);
        return NULL;
    }
}

bool CloudLayer::init(float width)
{
    if (Layer::init()) {
        this->setContentSize(BSWinSize());
        SpriteBatchNode *batch_ = SpriteBatchNode::create("cloud_1.png",10);
        this->addChild(batch_);
        
        float curWidth_ = 0;
        int iCount = 0;
        float spWidth = 0.0f;
        while (curWidth_<width) {
            iCount++;
            Sprite* spCloud = Sprite::create("cloud_1.png");
            spCloud->setAnchorPoint(Point(0,0));
            batch_->addChild(spCloud);
            spWidth = spCloud->getContentSize().width;
            int iBig = 7;
            int iSmall = 5;
            if (_cloudDepth == kCloudBack)
            {
                iBig = 6;
                iSmall = 3;
            }
            int iRand_=iSmall + rand() % (iBig-iSmall+1);//3-7 rand
            CCLOG("iRand = %d",iRand_);
            
            spCloud->setOpacity(255*(iRand_/10.0));
            CCLOG("cur=%f",curWidth_);
            spCloud->setPosition(Point(curWidth_,0));
            
            
            //循环动画
            float moveTime2_ = 1+1*CCRANDOM_0_1();
            Point movePosition1_ = Point(spCloud->getPositionX(),
                                         -10-20*CCRANDOM_0_1());
            MoveTo *move1_ = MoveTo::create(moveTime2_,movePosition1_);
            EaseSineInOut *ease1_ = CCEaseSineInOut::create(move1_);
            Point movePosition2_ = Point(spCloud->getPositionX(),0);
            MoveTo *move2_ = MoveTo::create(moveTime2_,movePosition2_);
            EaseSineInOut *ease2_ = EaseSineInOut::create(move2_);
            Sequence *sequence1_ = Sequence::create(ease1_,ease2_,NULL);
            RepeatForever *repeat_ = RepeatForever::create(sequence1_);
            spCloud->runAction(repeat_);
            curWidth_+= spCloud->getContentSize().width;
        }
        
        _cloudLayerWidth = iCount*spWidth;
        CCLOG("icount = %d,%f",iCount,_cloudLayerWidth);

        return true;
    }
    else
    {
        return false;
    }
}

void CloudLayer::onEnter()
{
    Layer::onEnter();
}


void CloudLayer::onExit()
{
    Layer::onExit();
}






