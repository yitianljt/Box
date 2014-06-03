//
//  BaseCommon.h
//  ShareTest
//
//  Created by jintao on 14-5-18.
//
//

#ifndef __ShareTest__BaseCommon__
#define __ShareTest__BaseCommon__

#include <iostream>
#include "cocos2d.h"


class BaseComScene : public cocos2d::CCScene{

    
private:
    std::vector<std::string> notificationValues;
    
public:
    
    virtual bool init();
    ~BaseComScene();
    
    
};

/*
cocos2d::CCPoint BSMiddlePos(cocos2d::CCNode* pNode) {
    return ccp(pNode->getContentSize().width/2, pNode->getContentSize().height/2);
}


cocos2d::CCSize BSWinSize() {
    return cocos2d::CCDirector::sharedDirector()->getWinSize();
}*/
#endif /* defined(__ShareTest__BaseCommon__) */
